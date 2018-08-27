#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>

#include "gui.h"

struct Args
{
    int argc;
    char **argv;
};


void thread_gui(Args args)
{
    std::cout << "GUI: starting thread .." << std::endl;
    
    auto app = Gtk::Application::create(args.argc, args.argv, 
            "com.github.fdcl-gwu");
    Gui gui;
    app->run(gui.window);

    std::cout << "GUI: thread closed!" << std::endl;
}


void thread_camera(void)
{
    std::cout << "CAM: starting thread .." << std::endl;
    
    std::cout << "CAM: thread closed!" << std::endl;
}



int main(int argc, char *argv[]) 
{
    Args args;
    args.argc = argc;
    args.argv = argv;

    std::thread t1(thread_gui, args);
    std::thread t2(thread_camera);

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
