// camera.cpp
#include <opencv2/opencv.hpp>
#include <mutex>

cv::Mat latest_frame;
std::mutex frame_mutex;

void start_camera()
{
    cv::VideoCapture cap(0);  // camera index
    while (true)
    {
        cv::Mat frame;
        cap >> frame;
        if (!frame.empty())
        {
            std::lock_guard<std::mutex> lock(frame_mutex);
            latest_frame = frame.clone();
        }
    }
}
