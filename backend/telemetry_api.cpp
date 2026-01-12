// telemetry_api.cpp
#include "crow.h"
#include "api_keys.h"
#include <nlohmann/json.hpp>

extern std::atomic<float> battery_voltage;
extern std::atomic<float> altitude;

void telemetry_route(crow::SimpleApp& app)
{
    CROW_ROUTE(app, "/telemetry").methods("GET"_method)
    ([](const crow::request& req) {
        if (req.get_header_value("X-API-KEY") != TELEMETRY_API_KEY)
            return crow::response(403, "Invalid API Key");

        nlohmann::json j;
        j["battery_voltage"] = battery_voltage.load();
        j["altitude"] = altitude.load();

        return crow::response(j.dump());
    });
}
