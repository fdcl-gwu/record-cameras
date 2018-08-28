#include "camera.h"


Camera::Camera(int cam_num_in, System &SYS_IN) : cam_num(cam_num_in),
SYS(SYS_IN)
{
    Camera::init();
}


Camera::~Camera()
{
    ;
}


void Camera::sleep(void)
{
    usleep(200000); // 200 millis
}


void Camera::init(void)
{
    cv::VideoCapture cap(cam_num);

    try
    {
        int ret = cap.isOpened();
        std::cout << ret << cap.isOpened();

        if (cap.isOpened()) 
        {
            camera_detected = true;
            std::cout << get_time() << "CAM" << cam_num << ": camera detected"
                      << std::endl;
        }
    }
    catch(...)
    {
        camera_detected = false;
        std::cout << get_time() << "CAM" << cam_num << ": camera not detected"
                  << std::endl;

    }
}


void Camera::loop(void)
{
    if (camera_detected)
    {
        ;
    }
    else
    {
        Camera::sleep();
    }
}
