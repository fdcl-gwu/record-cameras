#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <gtkmm.h>
#include <string>
#include <opencv2/opencv.hpp>

#include <cairomm/context.h>
#include <giomm/resource.h>
#include <gdkmm/general.h> // set_source_pixbuf()
#include <glibmm/fileutils.h>

#include "types.h"
#include "common_funcs.h"


class Gui
{
public:
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create();
    Gtk::Window window;
    Gtk::Box *vbox_main, *hbox_main, *vbox_controls, *vbox_canvas;
    Gtk::Grid *grid_camera_data;
    Gtk::Button *btn_record, *btn_pause, *btn_refresh;
    Gtk::Statusbar *statusbar;
    Gtk::CheckButton *checkbox_cam0, *checkbox_cam1, *checkbox_cam2;
    Gtk::DrawingArea *draw_cam0, *draw_cam1;
    System &SYS;
    Gui(
            System &SYS_IN
    );
    ~Gui(void);
    void run(void);

private:
    void init(void);
    void on_btn_record_clicked(void);
    void on_btn_refresh_clicked(void);
    bool update(void);
    bool quit_program(GdkEventAny *event);

    std::string t_now;
    unsigned int context_id;

    Glib::RefPtr<Gdk::Pixbuf> m_image;
    void refresh_camera_check_boxes(void);
    void on_cam0_toggled(void);
    void on_cam1_toggled(void);
    void on_cam2_toggled(void);
protected:
    bool on_draw_0(const Cairo::RefPtr<Cairo::Context>& cr);
    bool on_draw_1(const Cairo::RefPtr<Cairo::Context>& cr);
};


#endif
