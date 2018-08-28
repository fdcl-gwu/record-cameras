#include <iostream>
#include <thread>
#include <unistd.h>

#include "gui.h"
#include "camera.h"
#include "types.h"


System SYS;


void thread_gui(Params params)
{
    std::cout << get_time() <<  "GUI: starting thread .." << std::endl;

    auto app = Gtk::Application::create(SYS.argc, SYS.argv,
            "com.github.fdcl-gwu");
    Gui gui(SYS);
    app->run(gui.window);

    std::cout << get_time() << "GUI: thread closed!" << std::endl;
}


void thread_camera(Params params)
{
    std::cout << get_time() << "CAM" << params.cam_num << ": starting thread .."
              << std::endl;

    Camera CAM(params.cam_num, SYS);
    while(SYS.on)
    {
        CAM.loop();
    }
    std::cout << get_time() << "CAM: thread closed!" << std::endl;
}



int main(int argc, char *argv[])
{
    Params params;
    params.argc = argc;
    params.argv = argv;

    SYS.on = true;

    std::cout << get_time() << "starting threads .." << std::endl;
    std::thread t1(thread_gui, params);
    params.cam_num = 0; std::thread t2(thread_camera, params);
    params.cam_num = 1; std::thread t3(thread_camera, params);
    params.cam_num = 2; std::thread t4(thread_camera, params);
    params.cam_num = 3; std::thread t5(thread_camera, params);
    params.cam_num = 4; std::thread t6(thread_camera, params);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();

    std::cout << get_time() << "program closed!" << std::endl;
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
