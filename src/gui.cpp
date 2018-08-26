#include "gui.h"


GUI::GUI(){
    GUI::init();
}


GUI::~GUI(){}


void GUI::init(void)
{
    app = Gtk::Application::create();
}
