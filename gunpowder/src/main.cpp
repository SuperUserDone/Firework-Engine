#include <iostream>
#include <memory>

#include <core/Scene.hpp>
#include <core/components/ComponentMaterial.hpp>
#include <core/components/ComponentMesh.hpp>
#include <core/components/ComponentMeshLoader.hpp>
#include <core/components/ComponentTransform.hpp>
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
    // renderer.add_pipeline_step(FW::Render::RENDERPASS_UI);
    renderer.add_pipeline_step(FW::Render::RENDERPASS_DONE);

    renderer.set_forward_buffer(std::make_shared<FW::Render::Framebuffer>(
        settings.width, settings.height, true, 8));

    auto postbuffer = std::make_shared<FW::Render::Framebuffer>(512, 512, true);
    // 0);
    renderer.set_postprocess_buffer(postbuffer);

    auto obj = std::make_shared<FW::Core::ObjectBasic>();
    auto mesh = std::make_shared<FW::Core::ComponentMeshLoader>(
        "./assets/models/sphere.fbx");
    auto mat = std::make_shared<FW::Core::ComponentMaterial>(
        "assets/materials/testmat.json");

    auto trans = std::make_shared<FW::Core::ComponentTransform>();

    obj->add_component(mat);
    obj->add_component(trans);
    obj->add_component(mesh);

    auto camera = std::make_shared<FW::Core::ObjectCamera>();

    FW::Core::ScenePtr test_scene = std::make_shared<FW::Core::Scene>();
    test_scene->add_object(obj);
    test_scene->add_camera(camera);

    auto cam_trans = std::dynamic_pointer_cast<FW::Core::ComponentTransform>(
        camera->get_components()[0]);

    FW::Input::InputWindow::set_resize_provider(FW::Input::WINDOW_SOURCE_IMGUI);

    while (!win.check_close())
    {
        static ImVec2 lastsize = {800, 600};
        if (renderer.smart_frame(test_scene))
        {
            trans->rotate(glm::vec3(0, 0, glm::radians(0.03f)));

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::DockSpaceOverViewport();

            ImGui::Begin("Scene");

            ImVec2 size = ImGui::GetWindowContentRegionMax();

            // ImVec2 size = ImGui::GetWindowSize();
            if (size.x != lastsize.x || size.y != lastsize.y)
            {
                lastsize = size;
                FW::Input::InputWindow::imgui_resize_callback(
                    size.x, size.y - 35 > 10 ? size.y - 35 : 10);
            }

            ImGui::Image((void *)(intptr_t)postbuffer->get_texture(),
                         ImVec2(size.x, size.y - 35 > 10 ? size.y - 35 : 10));

            ImGui::End();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            win.swap_buffers();
        }

        win.poll_events();
    }

    return 0;
}