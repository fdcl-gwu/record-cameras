#include "gui.h"


GUI::GUI(){
    GUI::init();
}


GUI::~GUI(){}


void GUI::init(void)
{
    app = Gtk::Application::create();

    builder = Gtk::Builder::create();
    try
    {
        builder->add_from_file("../recorder.glade");
    }
    catch (const Glib::FileError &ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
    }

}
