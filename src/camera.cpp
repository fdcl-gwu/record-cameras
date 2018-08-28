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
    title << "Camera " << cam_num;

    try
    {
        cap.open(cam_num);
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
        Camera::show_image();
    }
    else
    {
        Camera::sleep();
    }
}


void Camera::show_image(void)
{
    while (SYS.on)
    {
        cap >> image_in;
        if (image_in.empty()) break;

        image_in.copyTo(image);
        
        SYS.im_cam0 = image;

        // cv::imshow(Camera::title, image);
        // cv::imshow("C", image);
        //
        // char key = (char) cv::waitKey(10);
        // if (key == 27) break;
    }
}
