# Base Station Prototype

## Setup
1. Create virtual env:
   - Windows:
     python -m venv venv
     .\venv\Scripts\activate
   - Linux/macOS:
     python3 -m venv venv
     source venv/bin/activate

2. Install:
   pip install -r requirements.txt

3. Add a sample video (optional):
   Put a short `sample.mp4` into the `static/` folder.

4. Run:
   python app.py

5. Open:
   http://localhost:5000

Notes:
- The app currently simulates telemetry. Later you'll replace the simulator with a UDP/TCP/serial receiver.
- The channel switch button is a UI placeholder — implementation depends on your radio hardware.
