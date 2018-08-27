#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <chrono>
#include <gtkmm.h>
#include <string>

#include "types.h"


class Gui
{
public:
    // Glib::RefPtr<Gtk::Application> app;
    Gtk::Window window;
    Gtk::Box *vbox_main, *hbox_main, *vbox_controls;
    Gtk::Grid *grid_camera_data;
    Gtk::Button *btn_record, *btn_pause, btn_refresh;
    Gtk::Statusbar *statusbar;
    Gtk::CheckButton *checkbox_cam0, *checkbox_cam1, *checkbox_cam2,
        *checkbox_cam3, *checkbox_cam4;

    System &SYS;
    Gui(
            System &SYS_IN
    );
    ~Gui();

private:
    void init(void);
    void on_btn_record_clicked(void);

    std::string get_time(void);
    std::string get_file_name(int cam_num);
    std::string t_now;
    unsigned int context_id;
};


#endif
