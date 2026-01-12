Working procedure:
Telemetry Radio → MAVLink → MAVSDK → Telemetry API
Camera → OpenCV → Snapshot API
UI Button → /snapshot
UI Report → /telemetry



UI calling backend
1. Snapshot(solar panel before and after cleaning):
curl -X POST http://localhost:8080/snapshot \
-H "X-API-KEY: CAMERA_KEY_123"

2. Telemetry
curl http://localhost:8080/telemetry \
-H "X-API-KEY: TELEM_KEY_456"
