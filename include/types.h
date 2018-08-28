#ifndef TYPES_H
#define TYPES_H

#include <opencv2/opencv.hpp>


struct System
{
    bool on = true;
    bool record = false;
    int argc;
    char **argv;

    cv::Mat im_cam0;
};


struct Params
{
    int argc;
    char **argv;
    int cam_num = 0;
};


#endif
