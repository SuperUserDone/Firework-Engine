#include <iostream>
#include <memory>

#include <core/Scene.hpp>
#include <core/components/ComponentMaterial.hpp>
#include <core/components/ComponentMesh.hpp>
#include <core/components/ComponentMeshLoader.hpp>
#include <core/components/ComponentTransform.hpp>
#include <input/InputKeyboard.hpp>
#include <input/InputMouse.hpp>
#include <input/InputWindow.hpp>
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
    renderer.add_pipeline_step(FW::Render::RENDERPASS_DONE);

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

    FW::Input::InputMouse::set_fps_cursor(true);

    bool fps = true;

    while (!win.check_close())
    {
        if (renderer.smart_frame(test_scene))
        {

            double posx = 0;
            double posy = 0;
            if (FW::Input::InputKeyboard::is_key_down(FW::Input::FW_KEY_ESCAPE))
            {
                FW::Input::InputMouse::set_fps_cursor(false);
                fps = false;
            }

            if (fps)
            {
                posx = FW::Input::InputMouse::get_mouse_x() -
                       FW::Input::InputWindow::get_window_width() / 2;
                posy = FW::Input::InputMouse::get_mouse_y() -
                       FW::Input::InputWindow::get_window_height() / 2;
                FW::Input::InputMouse::set_cursor_pos(
                    FW::Input::InputWindow::get_window_width() / 2,
                    FW::Input::InputWindow::get_window_height() / 2);
            }

            cam_trans->rotate(glm::vec3(glm::radians(-0.2f * posy), 0,
                                        glm::radians(-0.2f * posx)));

            glm::vec3 rot = cam_trans->get_rot();
            glm::vec3 direction;

            direction.x = sin(rot.z);
            direction.y = -cos(rot.z);
            direction.z = cos(rot.x);

            direction = glm::normalize(direction);

            if (FW::Input::InputKeyboard::is_key_down(FW::Input::FW_KEY_W))
            {
                cam_trans->translate(direction * glm::vec3(-0.03));
            }

            if (FW::Input::InputKeyboard::is_key_down(FW::Input::FW_KEY_S))
            {
                cam_trans->translate(direction * glm::vec3(0.03));
            }

            if (FW::Input::InputKeyboard::is_key_down(FW::Input::FW_KEY_A))
            {
                cam_trans->translate(
                    glm::normalize(glm::cross(direction, glm::vec3(0, 0, 1))) *
                    glm::vec3(0.03));
            }

            if (FW::Input::InputKeyboard::is_key_down(FW::Input::FW_KEY_D))
            {
                cam_trans->translate(
                    glm::normalize(glm::cross(direction, glm::vec3(0, 0, 1))) *
                    glm::vec3(-0.03));
            }

            win.swap_buffers();
        }
        win.poll_events();
    }

    return 0;
}