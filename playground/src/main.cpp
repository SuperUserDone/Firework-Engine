#include <iostream>

#include <window/Window.hpp>

int main()
{
    std::cout << "Test" << std::endl;

    FW::Window::WindowSettings settings;
    settings.title = "ABC";

    FW::Window::Window win(settings);

    while (!win.check_close())
    {
        glClear(GL_COLOR_BUFFER_BIT);
        win.swap_buffers();
        win.poll_events();
    }

    return 0;
}