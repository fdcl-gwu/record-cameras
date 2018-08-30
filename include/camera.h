#ifndef CAMERA_H
#define CAMERA_H

#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "types.h"
#include "common_funcs.h"

class Camera
{
public:
    System &SYS;
    int cam_num;
    bool camera_detected = false;
    cv::VideoCapture cap;
    int frame_width, frame_height, fps_in;
    cv::VideoWriter video_out;

    Camera(
        int cam_num_in,
        System &SYS_IN
    );
    ~Camera();

    void loop(void);
    void sleep(void);
    void init(void);

private:
    std::stringstream title;
    cv::Mat image, image_in;
    void show_image(void);
    bool recording = false;
    bool open_new_file = true;
    std::string get_file_name(int cam_num);
};

#endif
