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

    Camera(
        int cam_num_in,
        System &SYS_IN
    );
    ~Camera();

    void loop(void);
    void sleep(void);

private:
    void init(void);
};

#endif
