#include "gui.h"


Gui::Gui(System &SYS_IN) : SYS(SYS_IN)
{
    Gui::init();
}


Gui::~Gui()
{
    std::cout << get_time() << " GUI: setting system off .."
              << std::endl;
    SYS.on = false;
}


void Gui::on_btn_record_clicked(void)
{
    if (SYS.record)
    {
        SYS.record = false;
        btn_record->set_label("Record");
        std::cout << get_time() << "recording stopped" << std::endl;
        Gui::refresh_camera_check_boxes();
        statusbar->push("Recording stopped", context_id);
    }
    else
    {
        SYS.record = true;
        btn_record->set_label("Stop");
        checkbox_cam0->set_sensitive(false);
        checkbox_cam1->set_sensitive(false);
        checkbox_cam2->set_sensitive(false);
        std::cout << get_time() << "recording started" << std::endl;
        statusbar->push("Recording started", context_id);
    }
}


bool Gui::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cv::Mat mat1 = SYS.im_cam0;
    if (mat1.cols < 1) return false;

    Gdk::Cairo::set_source_pixbuf (cr,
            Gdk::Pixbuf::create_from_data(mat1.data, Gdk::COLORSPACE_RGB,
                false, 8, mat1.cols, mat1.rows, mat1.step));
    cr->paint();

    return true;
}


bool Gui::on_timeout(void)
{
    int h, w;
    Gui::draw_cam0->get_size_request(h, w);
    if (h == 641) Gui::draw_cam0->set_size_request(640, 480);
    else Gui::draw_cam0->set_size_request(641, 480);

    return true;
}



void Gui::init(void)
{
    window.set_default_size(400, 200);
    window.set_title("Record Cameras");

    // level 0
    // main container (this contains hbox_main and the statusbar)
    vbox_main = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 2));
    window.add(*vbox_main);

    // level 1
    // first child of vbox_main
    // contains the check buttons and labels for the camera data, and controls
    hbox_main = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 2));
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
    checkbox_cam0->set_sensitive(false);
    checkbox_cam0->signal_toggled().connect(sigc::mem_fun(*this,
                &Gui::on_cam0_toggled));
    grid_camera_data->attach(*checkbox_cam0, 0, 0, 1, 1);

    checkbox_cam1 = Gtk::manage(new Gtk::CheckButton("camera 1"));
    checkbox_cam1->set_size_request(200, 30);
    checkbox_cam1->set_sensitive(false);
    checkbox_cam1->signal_toggled().connect(sigc::mem_fun(*this,
                &Gui::on_cam1_toggled));
    grid_camera_data->attach(*checkbox_cam1, 0, 1, 1, 1);

    checkbox_cam2 = Gtk::manage(new Gtk::CheckButton("camera 2"));
    checkbox_cam2->set_size_request(200, 30);
    checkbox_cam2->set_sensitive(false);
    checkbox_cam2->signal_toggled().connect(sigc::mem_fun(*this,
                &Gui::on_cam2_toggled));
    grid_camera_data->attach(*checkbox_cam2, 0, 2, 1, 1);

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
    btn_record->signal_clicked().connect(sigc::mem_fun(*this,
                &Gui::on_btn_record_clicked));
    vbox_controls->pack_start(*btn_record, Gtk::PACK_SHRINK, 0);


    draw_cam0 = Gtk::manage(new Gtk::DrawingArea);
    draw_cam0->signal_draw().connect(sigc::mem_fun(*this, &Gui::on_draw));
    draw_cam0->set_size_request(640, 480);
    hbox_main->add(*draw_cam0);

    // level 1
    // second child of vbox_main
    // status bar
    statusbar = Gtk::manage(new Gtk::Statusbar);
    vbox_main->add(*statusbar);
    context_id = statusbar->get_context_id("");
    statusbar->push("Click Record to start recording", context_id);
    context_id++;

    int timeout_value = 40; //in ms
    sigc::slot<bool>my_slot = sigc::mem_fun(*this, &Gui::on_timeout);
    Glib::signal_timeout().connect(my_slot, timeout_value);

    vbox_main->set_focus_child(*hbox_main);
    hbox_main->set_focus_child(*vbox_controls);
    vbox_controls->set_focus_child(*btn_record);
    vbox_main->show_all();

    usleep(1e6);
    Gui::refresh_camera_check_boxes();
}


void Gui::refresh_camera_check_boxes(void)
{
    if (SYS.camera_detected[0]) checkbox_cam0->set_sensitive(true);
    else checkbox_cam0->set_sensitive(false);

    if (SYS.camera_detected[1]) checkbox_cam1->set_sensitive(true);
    else checkbox_cam1->set_sensitive(false);

    if (SYS.camera_detected[2]) checkbox_cam2->set_sensitive(true);
    else checkbox_cam2->set_sensitive(false);
}


void Gui::on_cam0_toggled(void)
{
    if(checkbox_cam0->get_active())
    {
        if (SYS.cam1_on && SYS.cam2_on)
        {
            statusbar->push("Only two cameras at a time", context_id);
            SYS.cam2_on = false;
            checkbox_cam2->set_active(false);
        }
        SYS.cam0_on = true;
    }
    else
    {
        SYS.cam0_on = false;
    }
}


void Gui::on_cam1_toggled(void)
{
    if(checkbox_cam1->get_active())
    {
        if (SYS.cam0_on && SYS.cam2_on)
        {
            statusbar->push("Only two cameras at a time", context_id);
            SYS.cam2_on = false;
            checkbox_cam2->set_active(false);
        }
        SYS.cam1_on = true;
    }
    else
    {
        SYS.cam1_on = false;
    }
}


void Gui::on_cam2_toggled(void)
{
    if(checkbox_cam2->get_active())
    {
        if (SYS.cam0_on && SYS.cam1_on)
        {
            statusbar->push("Only two cameras at a time", context_id);
            SYS.cam1_on = false;
            checkbox_cam1->set_active(false);
        }
        SYS.cam2_on = true;
    }
    else
    {
        SYS.cam2_on = false;
    }
}

