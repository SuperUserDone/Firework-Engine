#pragma once

#include <glibmm.h>
#include <gtkmm.h>

class WindowMain : public Gtk::ApplicationWindow
{
private:
    Gtk::Box m_menu_box;

    Gtk::MenuBar m_menu_bar;

    Gtk::MenuItem m_menu_item_cat_file;
    Gtk::Menu m_menu_file;
    Gtk::MenuItem m_menu_item_file_new;

public:
    WindowMain(Glib::RefPtr<Gtk::Application> app);
    ~WindowMain();
};
