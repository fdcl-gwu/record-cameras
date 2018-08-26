#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <gtkmm.h>


class Gui
{
public:
    // Glib::RefPtr<Gtk::Application> app;
    Gtk::Window window;
    Gtk::Box *vbox_main, *hbox_main, *vbox_controls;
    Gtk::Grid *grid_camera_data;
    Gtk::Button *btn_record, *btn_pause, btn_refresh;

    Gui();
    ~Gui();

private:
    void init(void);

};


#endif
