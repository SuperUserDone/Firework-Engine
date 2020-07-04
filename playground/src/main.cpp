#include <iostream>
#include <memory>

#include <core/Scene.hpp>
#include <core/components/ComponentMaterial.hpp>
#include <core/components/ComponentMesh.hpp>
#include <core/components/ComponentMeshLoader.hpp>
#include <core/components/ComponentTransform.hpp>
#include <render/CubeMap.hpp>
#include <render/Framebuffer.hpp>
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
    renderer.add_pipeline_step(FW::Render::RENDERPASS_POST_PROCESS);
    renderer.add_pipeline_step(FW::Render::RENDERPASS_UI);

    renderer.set_forward_buffer(std::make_shared<FW::Render::Framebuffer>(
        settings.width, settings.height, true, 8));

    renderer.set_postprocess_buffer(
        std::make_shared<FW::Render::Framebuffer>(0));

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

    test_scene->add_ui_element([cam_trans, camera]() {
        glm::vec3 pos = cam_trans->get_pos();
        glm::vec3 rot = cam_trans->get_rot();

        static glm::vec3 lookat_target(0, 0, 0);
        static bool camera_lookat = false;

        ImGui::Begin("Camera");
        ImGui::InputFloat3("Position", &pos[0], 4);
        ImGui::InputFloat3("Rotation", &rot[0], 4);
        ImGui::Checkbox("Camera target", &camera_lookat);
        ImGui::InputFloat3("Target", &lookat_target[0], 4);
        ImGui::End();

        cam_trans->set_pos(pos);
        cam_trans->set_rot(rot);
        if (camera_lookat)
            camera->look_at(lookat_target);
    });

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