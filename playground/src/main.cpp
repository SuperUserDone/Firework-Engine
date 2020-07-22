#include <iostream>
#include <memory>

#include <render/RenderServer.hpp>
#include <window/Window.hpp>

int main()
{

    FW::Window::WindowSettings settings;
    settings.title = "ABC";

    FW::Window::Window win(settings);

    FW::Render::RenderServer server(&win);

    while (!win.check_close())
    {
        win.poll_events();
        server.set_done();
    }

    return 0;
}