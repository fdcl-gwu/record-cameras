#include "gui.h"


Gui::Gui(System &SYS_IN) : SYS(SYS_IN)
{
    Gui::init();
}


Gui::~Gui()
{
    std::cout << "GUI: setting system off .." << std::endl;
    SYS.on = false;
}


void Gui::on_btn_record_clicked(void)
{
    if (SYS.record)
    {
        SYS.record = false;
        btn_record->set_label("Record");
        std::cout << get_time() << "recording stopped" << std::endl;
        statusbar->push("Recording stopped", context_id);
    }
    else
    {
        SYS.record = true;
        btn_record->set_label("Stop");
        std::cout << get_time() << "recording started" << std::endl;
        statusbar->push("Recording started", context_id);
    }
}


std::string Gui::get_file_name(int cam_num)
{
    time_t now = time(0);
    struct tm tstruct;
    char start_time[80];
    tstruct = *localtime(&now);
    strftime(start_time, sizeof(start_time), "%Y%m%d_%H%M%S", &tstruct);

    char t_now_char[256];
    sprintf(t_now_char, "%s_cam_%d", start_time, cam_num);

    return std::string(t_now_char);
}


bool Gui::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
    cv::Mat mat1 = SYS.im_cam0;
    // if (!mat1)
        // return false;

    // Gtk::Allocation allocation = get_allocation();
    // const int width = allocation.get_width();
    // const int height = allocation.get_height();
    std::cout << mat1.cols << " " << mat1.rows << std::endl;
    if (mat1.cols < 1) return false;

    Gdk::Cairo::set_source_pixbuf (cr, 
            Gdk::Pixbuf::create_from_data(mat1.data, Gdk::COLORSPACE_RGB, 
                false, 8, mat1.cols, mat1.rows, mat1.step));
    cr->paint();
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

    vbox_main->set_focus_child(*hbox_main);
    hbox_main->set_focus_child(*vbox_controls);
    vbox_controls->set_focus_child(*btn_record);
    vbox_main->show_all();
}
