#ifndef CAMERA_H
#define CAMERA_H

#include <opencv2/opencv.hpp>
#include "types.h"

class Camera
{
public:
    System &SYS;
    int cam_num;

    Camera(
        int cam_num_in,
        System &SYS_IN
    );
    ~Camera();
};

#endif
