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
            frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
            frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
            fps_in = cap.get(CV_CAP_PROP_FPS);
            SYS.camera_detected[cam_num] = true;
        }
    }
    catch(...)
    {
        camera_detected = false;
        std::cout << get_time() << "CAM" << cam_num << ": camera not detected"
                  << std::endl;
        SYS.camera_detected[cam_num] = false;

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
        if (image_in.empty()) continue;

        cv::cvtColor(image_in, image, CV_BGR2RGB);
        SYS.im_cam0 = image;

        if (SYS.record)
        {
            if (open_new_file)
            {
                std::string file_name = Camera::get_file_name(cam_num);
                video_out.open(file_name, CV_FOURCC('M','J','P','G'),
                    fps_in, cv::Size(frame_width, frame_height), true);
                open_new_file = false;
            }
            recording = true;
            video_out.write(image_in);
        }
        else
        {
            if (recording)
            {
                recording = false;
                video_out.release();
                open_new_file = true;
            }
        }
    }
}


std::string Camera::get_file_name(int cam_num)
{
    time_t now = time(0);
    struct tm tstruct;
    char start_time[80];
    tstruct = *localtime(&now);
    strftime(start_time, sizeof(start_time), "%Y%m%d_%H%M%S", &tstruct);

    char t_now_char[256];
    sprintf(t_now_char, "%s_cam_%d.avi", start_time, cam_num);

    return std::string(t_now_char);
}
