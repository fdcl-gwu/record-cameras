#include <opencv2/opencv.hpp>
#include <iostream>

#include "gui.h"


class Gui
{
public:
    // Glib::RefPtr<Gtk::Application> app;
    Gtk::Window window;
    Gtk::Box *vbox_main, *hbox_main, *vbox_controls;
    Gtk::Grid *grid_camera_data;
    Gtk::Button *btn_record, *btn_pause, btn_refresh;

    Gui()
    {
        Gui::init();
    }


private:
    void init(void)
    {
        window.set_default_size(400, 200);
        window.set_title("Record Cameras");

        // main container (this contains hbox_main and the statusbar)
        vbox_main = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
        window.add(*vbox_main);
        
        // first child of vbox_main
        // contains the check buttons and labels for the camera data
        hbox_main = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
        vbox_main->pack_start(*hbox_main, Gtk::PACK_SHRINK, 0);

        grid_camera_data = Gtk::manage(new Gtk::Grid);
        hbox_main->add(*grid_camera_data);

        vbox_controls = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
        hbox_main->add(*vbox_controls);
        
        btn_record = Gtk::manage(new Gtk::Button("Record"));
        vbox_controls->pack_start(*btn_record, Gtk::PACK_SHRINK, 0);

        vbox_main->show_all();
    }


};

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    std::cout << "Main" << std::endl;
    Gui gui;
    app->run(gui.window);
    std::cout << "Ending program" << std::endl;
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
