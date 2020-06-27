#include <iostream>

#include <core/Scene.hpp>
#include <core/components/ComponentMaterial.hpp>
#include <core/components/ComponentMesh.hpp>
#include <core/components/ComponentMeshLoader.hpp>
#include <render/Material.hpp>
#include <render/Renderer.hpp>
#include <window/Window.hpp>

int main()
{
    FW::Window::WindowSettings settings;
    settings.title = "ABC";

    FW::Window::Window win(settings);

    FW::Render::Renderer renderer;
    renderer.add_pipeline_step(FW::Render::RENDERPASS_RESET);
    renderer.add_pipeline_step(FW::Render::RENDERPASS_FORWARD);

    auto obj = std::make_shared<FW::Core::ObjectBasic>();
    auto mesh = std::make_shared<FW::Core::ComponentMeshLoader>(
        "./assets/models/monkey.fbx");
    auto mat = std::make_shared<FW::Core::ComponentMaterial>(
        "assets/materials/testmat.json");

    obj->add_component(mat);
    obj->add_component(mesh);

    auto camera = std::make_shared<FW::Core::ObjectCamera>();

    FW::Core::Scene test_scene;
    test_scene.add_object(obj);
    test_scene.add_camera(camera);

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