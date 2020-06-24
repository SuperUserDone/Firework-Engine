#include <iostream>

#include <core/Scene.hpp>
#include <core/components/ComponentMesh.hpp>
#include <render/Renderer.hpp>
#include <window/Window.hpp>

int main()
{
    std::cout << "Test" << std::endl;

    FW::Window::WindowSettings settings;
    settings.title = "ABC";

    FW::Window::Window win(settings);
    FW::Render::Renderer renderer;
    auto obj = std::make_shared<FW::Core::ObjectBasic>();
    auto mesh = std::make_shared<FW::Core::ComponentMesh>();
    obj->add_component(mesh);
    FW::Core::Scene test_scene;
    test_scene.add_object(obj);

    renderer.add_pipeline_step(FW::Render::RENDERPASS_RESET);
    renderer.add_pipeline_step(FW::Render::RENDERPASS_FORWARD);

    while (!win.check_close())
    {
        if (renderer.smart_frame(test_scene))
        {
            win.swap_buffers();
        }
        win.poll_events();
    }

    return 0;
}