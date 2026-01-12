// telemetry.cpp
#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/telemetry/telemetry.h>
#include <atomic>

using namespace mavsdk;

std::atomic<float> battery_voltage{0.0f};
std::atomic<float> altitude{0.0f};

void start_telemetry()
{
    Mavsdk mavsdk;
    mavsdk.add_any_connection("udp://0.0.0.0:14550");

    auto system = mavsdk.systems().at(0);
    Telemetry telemetry{system};

    telemetry.subscribe_battery([](Telemetry::Battery bat) {
        battery_voltage = bat.voltage_v;
    });

    telemetry.subscribe_position([](Telemetry::Position pos) {
        altitude = pos.relative_altitude_m;
    });
}
