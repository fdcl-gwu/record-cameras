#include "gui.h"



Gui::Gui()
{
    Gui::init();
}


Gui::~Gui()
{
    ; // do nothing
}


void Gui::init(void)
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

