#include "WindowMain.hpp"

WindowMain::WindowMain(Glib::RefPtr<Gtk::Application> app)
    : m_menu_box(Gtk::ORIENTATION_VERTICAL)
{
    set_name("Gunpowder Editor");

    m_menu_item_cat_file.set_label("File");
    m_menu_item_file_new.set_label("New");

    m_menu_item_cat_file.set_submenu(m_menu_file);

    m_menu_file.append(m_menu_item_file_new);

    m_menu_bar.append(m_menu_item_cat_file);

    m_menu_box.set_homogeneous(false);
    m_menu_box.pack_start(m_menu_bar, Gtk::PACK_SHRINK);
    add(m_menu_box);

    show_all_children();
}

WindowMain::~WindowMain() {}