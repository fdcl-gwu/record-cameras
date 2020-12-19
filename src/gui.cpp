#include "gui.h"


Gui::Gui(System &SYS_IN) : SYS(SYS_IN)
{
    Gui::init();
}


Gui::~Gui()
{
    std::cout << get_time() << "GUI: setting system off .."
              << std::endl;
    SYS.on = false;
}


void Gui::on_btn_record_clicked(void)
{
    if (SYS.record)
    {
        SYS.record = false;
        btn_record->set_image_from_icon_name("media-record");
        btn_record->set_tooltip_text("Start recording the video");
        std::cout << get_time() << "recording stopped" << std::endl;
        Gui::refresh_camera_check_boxes();
        btn_refresh->set_sensitive(true);
        statusbar->push("Recording stopped", context_id);
    }
    else
    {
        SYS.record = true;
        btn_record->set_image_from_icon_name("media-playback-stop");
        btn_record->set_tooltip_text("Stop recording the video");
        checkbox_cam0->set_sensitive(false);
        checkbox_cam1->set_sensitive(false);
        checkbox_cam2->set_sensitive(false);
        btn_refresh->set_sensitive(false);
        std::cout << get_time() << "recording started" << std::endl;
        statusbar->push("Recording started", context_id);
    }
}


void Gui::on_btn_refresh_clicked(void)
{
    statusbar->push("Refreshing cameras ..", context_id);
    checkbox_cam0->set_sensitive(false);
    checkbox_cam1->set_sensitive(false);
    checkbox_cam2->set_sensitive(false);
    btn_record->set_sensitive(false);
    Gui::refresh_camera_check_boxes();
    btn_record->set_sensitive(true);
    statusbar->push("Camera refresh completed", context_id);
}


bool Gui::on_draw_0(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cv::Mat mat;
    if (SYS.camera_on[0] && !SYS.camera_on[1] && !SYS.camera_on[2])
    {
        mat = SYS.im_cam[0];
    }
    else if (!SYS.camera_on[0] && SYS.camera_on[1] && !SYS.camera_on[2])
    {
        mat = SYS.im_cam[1];
    }
    else if (!SYS.camera_on[0] && !SYS.camera_on[1] && SYS.camera_on[2])
    {
        mat = SYS.im_cam[2];
    }
    else if (SYS.camera_on[0] && SYS.camera_on[1]) 
    {
        mat = SYS.im_cam[0];
    }
    else if (SYS.camera_on[0] && SYS.camera_on[2]) 
    {
        mat = SYS.im_cam[0];
    }
    else if (SYS.camera_on[1] && SYS.camera_on[2]) 
    {
        mat = SYS.im_cam[1];
    }

    if (mat.cols < 1) return false;

    Gdk::Cairo::set_source_pixbuf (cr,
            Gdk::Pixbuf::create_from_data(mat.data, Gdk::COLORSPACE_RGB,
                false, 8, mat.cols, mat.rows, mat.step));
    cr->paint();

    return true;
}


bool Gui::on_draw_1(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cv::Mat mat;
    if (SYS.camera_on[0] && SYS.camera_on[1]) 
    {
        mat = SYS.im_cam[1];
    }
    else if (SYS.camera_on[0] && SYS.camera_on[2]) 
    {
        mat = SYS.im_cam[2];
    }
    else if (SYS.camera_on[1] && SYS.camera_on[2]) 
    {
        mat = SYS.im_cam[2];
    }

    if (mat.cols < 1) return false;

    Gdk::Cairo::set_source_pixbuf (cr,
            Gdk::Pixbuf::create_from_data(mat.data, Gdk::COLORSPACE_RGB,
                false, 8, mat.cols, mat.rows, mat.step));
    cr->paint();

    return true;
}


bool Gui::update(void)
{
    Gui::draw_cam0->queue_draw();
    Gui::draw_cam1->queue_draw();

    if (!SYS.on)
    {
        std::cout << "GUI: closing window .." << std::endl;
        app->quit();
    }
    usleep(100);
    return true;
}


bool Gui::quit_program(GdkEventAny* event)
{
    SYS.on = false;
    return true;
}


void Gui::run(void)
{
    std::cout << "GUI: drawing window .." << std::endl;
    app->run(window);
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
    // contains the vbox_controls
    vbox_controls = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 2));
    vbox_controls->set_size_request(100, 200);
    hbox_main->pack_start(*vbox_controls, Gtk::PACK_SHRINK, 2);

    // level 3
    // first child of vbox_controls
    // contains the grid that holds check_buttons and the labels for camera
    // data
    grid_camera_data = Gtk::manage(new Gtk::Grid);
    grid_camera_data->set_size_request(150, 200);
    grid_camera_data->set_border_width(2);
    vbox_controls->add(*grid_camera_data);

    checkbox_cam0 = Gtk::manage(new Gtk::CheckButton("camera 0"));
    checkbox_cam0->set_size_request(100, 30);
    checkbox_cam0->set_sensitive(false);
    checkbox_cam0->signal_toggled().connect(sigc::mem_fun(*this,
                &Gui::on_cam0_toggled));
    grid_camera_data->attach(*checkbox_cam0, 0, 0, 1, 1);

    checkbox_cam1 = Gtk::manage(new Gtk::CheckButton("camera 1"));
    checkbox_cam1->set_size_request(100, 30);
    checkbox_cam1->set_sensitive(false);
    checkbox_cam1->signal_toggled().connect(sigc::mem_fun(*this,
                &Gui::on_cam1_toggled));
    grid_camera_data->attach(*checkbox_cam1, 0, 1, 1, 1);

    checkbox_cam2 = Gtk::manage(new Gtk::CheckButton("camera 2"));
    checkbox_cam2->set_size_request(100, 30);
    checkbox_cam2->set_sensitive(false);
    checkbox_cam2->signal_toggled().connect(sigc::mem_fun(*this,
                &Gui::on_cam2_toggled));
    grid_camera_data->attach(*checkbox_cam2, 0, 2, 1, 1);

    // level 3
    // second child of vbox_controls
    btn_record = Gtk::manage(new Gtk::Button());
    btn_record->set_image_from_icon_name("media-record");
    btn_record->set_tooltip_text("Start recording the video");
    btn_record->set_size_request(100, 100);
    btn_record->signal_clicked().connect(sigc::mem_fun(*this,
                &Gui::on_btn_record_clicked));
    vbox_controls->add(*btn_record);
    vbox_controls->grab_focus();


    // level 3
    // third child of vbox_controls
    btn_refresh = Gtk::manage(new Gtk::Button());
    btn_refresh->set_image_from_icon_name("view-refresh");
    btn_refresh->set_size_request(100, 30);
    btn_refresh->set_tooltip_text("Recheck for hardware changes");
    btn_refresh->signal_clicked().connect(sigc::mem_fun(*this,
                &Gui::on_btn_refresh_clicked));
    vbox_controls->add(*btn_refresh);

    // level 2
    // second child of hbox_main
    // contains the drawing canvases
    vbox_canvas = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    vbox_canvas->set_size_request(100, 200);
    vbox_canvas->set_border_width(2);
    hbox_main->add(*vbox_canvas);

    draw_cam0 = Gtk::manage(new Gtk::DrawingArea);
    draw_cam0->signal_draw().connect(sigc::mem_fun(*this, &Gui::on_draw_0));
    draw_cam0->set_size_request(640, 480);
    vbox_canvas->pack_start(*draw_cam0, Gtk::PACK_SHRINK, 2);

    draw_cam1 = Gtk::manage(new Gtk::DrawingArea);
    draw_cam1->signal_draw().connect(sigc::mem_fun(*this, &Gui::on_draw_1));
    draw_cam1->set_size_request(640, 480);
    vbox_canvas->add(*draw_cam1);

    // level 1
    // second child of vbox_main
    // status bar
    statusbar = Gtk::manage(new Gtk::Statusbar);
    vbox_main->add(*statusbar);
    context_id = statusbar->get_context_id("");
    statusbar->push("Click Record to start recording", context_id);
    context_id++;

    // int timeout_value = 40; //in ms
    // sigc::slot<bool>my_slot = sigc::mem_fun(*this, &Gui::on_timeout);
    // Glib::signal_timeout().connect(my_slot, timeout_value);

    vbox_main->set_focus_child(*hbox_main);
    hbox_main->set_focus_child(*vbox_controls);
    vbox_controls->set_focus_child(*btn_record);
    vbox_main->show_all();

    Gui::refresh_camera_check_boxes();

    Glib::signal_idle().connect(sigc::mem_fun(*this, &Gui::update));

    window.signal_delete_event().connect(sigc::mem_fun(*this, \
        &Gui::quit_program));
}


void Gui::refresh_camera_check_boxes(void)
{
    SYS.refresh_cameras = true;
    usleep(1e6);
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
        if (SYS.camera_on[1] && SYS.camera_on[2])
        {
            statusbar->push("Only two cameras at a time", context_id);
            SYS.camera_on[2] = false;
            checkbox_cam2->set_active(false);
        }
        SYS.camera_on[0] = true;
    }
    else
    {
        SYS.camera_on[0] = false;
    }
}


void Gui::on_cam1_toggled(void)
{
    if(checkbox_cam1->get_active())
    {
        if (SYS.camera_on[0] && SYS.camera_on[2])
        {
            statusbar->push("Only two cameras at a time", context_id);
            SYS.camera_on[2] = false;
            checkbox_cam2->set_active(false);
        }
        SYS.camera_on[1] = true;
    }
    else
    {
        SYS.camera_on[1] = false;
    }
}


void Gui::on_cam2_toggled(void)
{
    if(checkbox_cam2->get_active())
    {
        if (SYS.camera_on[0] && SYS.camera_on[1])
        {
            statusbar->push("Only two cameras at a time", context_id);
            SYS.camera_on[1] = false;
            checkbox_cam1->set_active(false);
        }
        SYS.camera_on[2] = true;
    }
    else
    {
        SYS.camera_on[2] = false;
    }
}
