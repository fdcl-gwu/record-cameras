#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <unistd.h>

#include "gui.h"
#include "types.h"


System SYS;


void thread_gui(Params params)
{
    std::cout << "GUI: starting thread .." << std::endl;
    
    auto app = Gtk::Application::create(SYS.argc, SYS.argv, 
            "com.github.fdcl-gwu");
    Gui gui(SYS);
    app->run(gui.window);

    std::cout << "GUI: thread closed!" << std::endl;
}


void thread_camera(Params params)
{
    std::cout << "CAM" << params.cam_num << ": starting thread .." 
              << std::endl;
    while(SYS.on)
    {
        usleep(10);
    }
    std::cout << "CAM: thread closed!" << std::endl;
}



int main(int argc, char *argv[]) 
{
    Params params;
    params.argc = argc;
    params.argv = argv;

    SYS.on = true;

    std::thread t1(thread_gui, params);
    std::thread t2(thread_camera, params);

    t1.join();
    t2.join();

    std::cout << "Program closed!" << std::endl;
    return 0;
}

//
// int main(int argc, char **argv)
// {
//     auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
//     auto builder = Gtk::Builder::create();
//     builder->add_from_file("../recorder.glade");
//
//     Gtk::Window* window;
//     builder->get_widget("main_window", window);
//     // app->run(window);
//     // window->show();
//
//     // GUI gui;
//     //
//     // Gtk::Main recorder(argc, argv);
//     // recorder.run();
//
//     // int wait_time = 10;
//     // cv::VideoCapture in_video;
//     // in_video.open(0);
//     //
//     // while (in_video.grab())
//     // {
//     //     cv::Mat image, image_copy;
//     //     in_video.retrieve(image);
//     //     image.copyTo(image_copy);
//     //
//     //     cv::imshow("Camers View", image_copy);
//     //     char key = (char) cv::waitKey(wait_time);
//     //     if (key == 27)
//     //         break;
//     // }
//     //
//     // in_video.release();
//
//     return 0;
// }
