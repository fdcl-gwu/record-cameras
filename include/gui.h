#ifndef GUI_H
#define GUI_H

#include <gtkmm.h>


class GUI
{
public:
    GUI();
    ~GUI();

    Glib::RefPtr<Gtk::Application> app;


private:
    void init(void);
};


#endif
