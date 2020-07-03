#include <iostream>
#include <memory>

#include <core/Scene.hpp>
#include <core/components/ComponentMaterial.hpp>
#include <core/components/ComponentMesh.hpp>
#include <core/components/ComponentMeshLoader.hpp>
#include <core/components/ComponentTransform.hpp>
#include <render/CubeMap.hpp>
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
        "./assets/models/sphere.fbx");
    auto mat = std::make_shared<FW::Core::ComponentMaterial>(
        "assets/materials/testmat.json");

    auto trans = std::make_shared<FW::Core::ComponentTransform>();

    FW::Render::CubeMap map("assets/materials/textures/skybox/irr.png");
    map.async_safe_load();
    map.sync_only_load();
    map.bind(4);

    FW::Render::CubeMap map1("assets/materials/textures/skybox/rad_[6].png");
    map1.async_safe_load();
    map1.sync_only_load();
    map1.bind(5);

    FW::Render::Texture brdf_lut("assets/materials/textures/ibl_brdf_lut.png");
    brdf_lut.async_safe_load();
    brdf_lut.sync_only_load();
    brdf_lut.bind(6);

    obj->add_component(mat);
    obj->add_component(trans);
    obj->add_component(mesh);

    auto camera = std::make_shared<FW::Core::ObjectCamera>();

    FW::Core::ScenePtr test_scene = std::make_shared<FW::Core::Scene>();
    test_scene->add_object(obj);
    test_scene->add_camera(camera);

    auto cam_trans = std::dynamic_pointer_cast<FW::Core::ComponentTransform>(
        camera->get_components()[0]);

    while (!win.check_close())
    {
        if (renderer.smart_frame(test_scene))
        {
            trans->rotate(glm::vec3(0, 0, glm::radians(0.03f)));
            win.swap_buffers();
        }
        win.poll_events();
    }

    return 0;
}