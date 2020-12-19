#include "camera.h"


Camera::Camera(int cam_num_in, System &SYS_IN) : cam_num(cam_num_in),
SYS(SYS_IN)
{
    Camera::init();
}


Camera::~Camera()
{
    if (SYS.camera_open[cam_num])
    {
        cap.release();
        SYS.camera_open[cam_num] = false;
    }
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
        bool ret = cap.open(cam_num);
        if (ret && cap.isOpened())
        {
            camera_detected = true;
            std::cout << get_time() << "CAM" << cam_num << ": camera detected"
                      << std::endl;
            frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
            frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
            std::cout << get_time()
                      << "CAM" << cam_num << ": "
                      << "frame width " << " " << frame_width << " "
                      << "frame height " << frame_height
                      << std::endl;
            fps_in = cap.get(CV_CAP_PROP_FPS);
            SYS.camera_detected[cam_num] = true;
        }

        if (ret)
        {
            cap.release();
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
        if (SYS.camera_on[cam_num])
        {
            if (!SYS.camera_open[cam_num])
            {
                cap.open(cam_num);
                SYS.camera_open[cam_num] = true;
            }

            cap >> image_in;
            if (image_in.empty()) continue;

            cv::cvtColor(image_in, image, CV_BGR2RGB);
            SYS.im_cam[cam_num] = image;

            if (SYS.record) Camera::start_recording();
            else Camera::end_recording();
        }
        else
        {
            if (SYS.camera_open[cam_num])
            {
                cap.release();
                SYS.camera_open[cam_num] = false;
            }

            Camera::sleep();
        }
    }
}


void Camera::start_recording(void)
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


void Camera::end_recording(void)
{
    if (recording)
    {
        recording = false;
        video_out.release();
        open_new_file = true;
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
