#include <iostream>
#include <memory>

#include <gtkmm.h>

#include "WindowMain.hpp"


int main()
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create();

    WindowMain win(app);

    win.set_default_size(800, 600);

    return app->run(win);
}