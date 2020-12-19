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
    gui.run();

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

        if (SYS.refresh_cameras)
        {
            SYS.refresh_cameras = false;
            CAM.init();
        }
    }
    std::cout << get_time() << "CAM" << params.cam_num << ": thread closed!"
              << std::endl;
}



int main(int argc, char *argv[])
{
    Params params;
    params.argc = argc;
    params.argv = argv;

    SYS.on = true;

    std::cout << get_time() << "starting threads .." << std::endl;
    std::thread t1(thread_gui, params);
    params.cam_num = 0; std::thread t2(thread_camera, params); usleep(100000);
    params.cam_num = 1; std::thread t3(thread_camera, params); usleep(100000);
    params.cam_num = 2; std::thread t4(thread_camera, params); usleep(100000);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << get_time() << "program closed!" << std::endl;
    return 0;
}
