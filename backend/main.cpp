// main.cpp
#include "crow.h"
#include <thread>

void start_telemetry();
void start_camera();
void snapshot_route(crow::SimpleApp&);
void telemetry_route(crow::SimpleApp&);

int main()
{
    std::thread telemetry_thread(start_telemetry);
    std::thread camera_thread(start_camera);

    crow::SimpleApp app;
    snapshot_route(app);
    telemetry_route(app);

    app.port(8080).run();

    telemetry_thread.join();
    camera_thread.join();
}
