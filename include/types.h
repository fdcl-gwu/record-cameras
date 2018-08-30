#ifndef TYPES_H
#define TYPES_H

#include <opencv2/opencv.hpp>


struct System
{
    bool on = true;
    bool record = false;
    int argc;
    char **argv;
    bool camera_detected[3] = {false, false, false};
    bool cam0_on = false, cam1_on = false, cam2_on = false;
    bool camera_on[3] = {false, false, false};
    bool refresh_cameras = false;
    cv::Mat im_cam0, im_cam1, im_cam2;
};


struct Params
{
    int argc;
    char **argv;
    int cam_num = 0;
};


#endif
