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
    
    // level 0
    // main container (this contains hbox_main and the statusbar)
    vbox_main = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    window.add(*vbox_main);

    // level 1
    // first child of vbox_main
    // contains the check buttons and labels for the camera data, and controls
    hbox_main = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 0));
    hbox_main->set_size_request(400, 200);
    vbox_main->pack_start(*hbox_main, Gtk::PACK_SHRINK, 0);

    // level 2
    // first child of hbox_main
    // the contains the grid that holds check_buttons and the labels for camera
    // data
    grid_camera_data = Gtk::manage(new Gtk::Grid);
    grid_camera_data->set_size_request(300, 200);
    grid_camera_data->set_border_width(2);
    hbox_main->add(*grid_camera_data);
    
    checkbox_cam0 = Gtk::manage(new Gtk::CheckButton("camera 0"));
    checkbox_cam0->set_size_request(200, 30);
    grid_camera_data->attach(*checkbox_cam0, 0, 0, 1, 1);

    checkbox_cam0 = Gtk::manage(new Gtk::CheckButton("camera 1"));
    checkbox_cam0->set_size_request(200, 30);
    grid_camera_data->attach(*checkbox_cam0, 0, 1, 1, 1);

    checkbox_cam0 = Gtk::manage(new Gtk::CheckButton("camera 2"));
    checkbox_cam0->set_size_request(200, 30);
    grid_camera_data->attach(*checkbox_cam0, 0, 2, 1, 1);
    
    checkbox_cam0 = Gtk::manage(new Gtk::CheckButton("camera 3"));
    checkbox_cam0->set_size_request(200, 30);
    grid_camera_data->attach(*checkbox_cam0, 0, 3, 1, 1);
  
    checkbox_cam0 = Gtk::manage(new Gtk::CheckButton("camera 4"));
    checkbox_cam0->set_size_request(200, 30);
    grid_camera_data->attach(*checkbox_cam0, 0, 4, 1, 1);
    
    // level 2
    // second child of hbox_main
    // contains the controls
    vbox_controls = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    vbox_controls->set_size_request(100, 200);
    vbox_controls->set_border_width(2);
    hbox_main->add(*vbox_controls);
    vbox_controls->grab_focus();
 
    // level 3
    // first child of vbox_controls
    // start/stop recording
    btn_record = Gtk::manage(new Gtk::Button("Record"));
    btn_record->set_size_request(100, 100);
    vbox_controls->pack_start(*btn_record, Gtk::PACK_SHRINK, 0);

    // level 1
    // second child of vbox_main
    // TODO: add status bar
    
    vbox_main->show_all();
}

