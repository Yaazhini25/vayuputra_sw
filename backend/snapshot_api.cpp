// snapshot_api.cpp
#include "crow.h"
#include "api_keys.h"
#include <opencv2/opencv.hpp>
#include <ctime>

extern cv::Mat latest_frame;
extern std::mutex frame_mutex;

void snapshot_route(crow::SimpleApp& app)
{
    CROW_ROUTE(app, "/snapshot").methods("POST"_method)
    ([](const crow::request& req) {
        if (req.get_header_value("X-API-KEY") != CAMERA_API_KEY)
            return crow::response(403, "Invalid API Key");

        std::lock_guard<std::mutex> lock(frame_mutex);
        if (latest_frame.empty())
            return crow::response(500, "No frame");

        std::string filename = "snapshot_" + std::to_string(time(0)) + ".jpg";
        cv::imwrite(filename, latest_frame);

        return crow::response("Snapshot saved");
    });
}
