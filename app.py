from flask import Flask, render_template, request, jsonify
from flask_socketio import SocketIO

app = Flask(__name__)
app.config['SECRET_KEY'] = 'change-me'
socketio = SocketIO(app, async_mode='threading', cors_allowed_origins='*')


# Shared state (latest telemetry values)
latest_telemetry = {
    "lat": 12.9716,
    "lon": 77.5946,
    "alt": 5.0,
    "speed": 0.0,
    "battery": 100.0,
    "orientation": {"yaw": 0.0, "pitch": 0.0, "roll": 0.0},
    "rssi": 100.0,
}

# ---------------- ROUTES ----------------

@app.route('/')
def index():
    """Main dashboard UI."""
    return render_template('index.html')

@app.route('/api/telemetry', methods=['POST'])
def receive_telemetry():
    """Receive JSON telemetry from hardware and broadcast to dashboard."""
    try:
        data = request.get_json(force=True)
        update_telemetry(data)
        return jsonify({"ok": True}), 200
    except Exception as e:
        return jsonify({"ok": False, "error": str(e)}), 400

# ---------------- SOCKET.IO ----------------

@socketio.on('connect')
def on_connect():
    print("✅ Dashboard connected")
    # Send last known telemetry immediately to new connection
    socketio.emit('telemetry', latest_telemetry)

@socketio.on('request_channel_switch')
def on_channel_switch(data):
    """Optional: handle manual RF channel switch request."""
    print("⚙️ Channel switch requested:", data)
    socketio.emit('channel_switch_ack', {"ok": True, **(data or {})})

# ---------------- HELPERS ----------------

def update_telemetry(data):
    """Update shared telemetry and broadcast to all clients."""
    global latest_telemetry
    latest_telemetry.update({k: v for k, v in data.items() if k in latest_telemetry})
    if 'orientation' in data and isinstance(data['orientation'], dict):
        latest_telemetry['orientation'].update(data['orientation'])
    socketio.emit('telemetry', latest_telemetry)

# ---------------- MAIN ----------------

if __name__ == '__main__':
    print("\n🚀 Base Station running successfully!")
    print("👉 Open http://127.0.0.1:5000\n")
    socketio.run(app, host='127.0.0.1', port=5000, debug=True)
