#include <iostream>

#include <core/Scene.hpp>
#include <render/Renderer.hpp>
#include <window/Window.hpp>

int main()
{
    std::cout << "Test" << std::endl;

    FW::Window::WindowSettings settings;
    settings.title = "ABC";

    FW::Window::Window win(settings);
    FW::Render::Renderer renderer;
    FW::Core::Scene test_scene;

    renderer.add_pipeline_step(FW::Render::RENDERPASS_FORWARD);

    while (!win.check_close())
    {
        if(renderer.smart_frame(test_scene));
        {
            win.swap_buffers();
            glClear(GL_COLOR_BUFFER_BIT);
        }
        win.poll_events();
    }

    return 0;
}