#ifndef GUI_H
#define GUI_H

#include <iostream>
#include <gtkmm.h>


class GUI
{
public:
    GUI();
    ~GUI();

    Glib::RefPtr<Gtk::Application> app;
    Glib::RefPtr<Gtk::Builder> builder;


private:
    void init(void);
    void build_from_glade(void);
};


#endif
