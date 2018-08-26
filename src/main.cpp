#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

#include "gui.h"

int main(int argc, char **argv)
{
    GUI GUI;
    int wait_time = 10;
    cv::VideoCapture in_video;
    in_video.open(0);

    while (in_video.grab()) 
    {
        cv::Mat image, image_copy;
        in_video.retrieve(image);
        image.copyTo(image_copy);

        cv::imshow("Camers View", image_copy);
        char key = (char) cv::waitKey(wait_time);
        if (key == 27)
            break;
    }

    in_video.release();
}
