#include <iostream>
#include <memory>

#include <core/manager/AssetManager.hpp>
#include <core/misc/Texture.hpp>
#include <render/RenderServer.hpp>
#include <render/RendererMesh.hpp>
#include <window/Window.hpp>

int main()
{
    FW::Window::WindowSettings settings;
    settings.title = "ABC";

    FW::Render::RenderServer &server = FW::Render::RenderServer::init(settings);

    FW::Core::AssetManager::init("assets/bundle_index.json");

    std::vector<FW::Core::Vertex> vertex_data;
    FW::Core::Vertex vert;
    vert.pos = {0.5f, 0.5f, 0.0f};
    vertex_data.push_back(vert);
    vert.pos = {0.5f, -0.5f, 0.0f};
    vertex_data.push_back(vert);
    vert.pos = {-0.5f, 0.5f, 0.0f};
    vertex_data.push_back(vert);
    vert.pos = {-0.5f, -0.5f, 0.0f};
    vertex_data.push_back(vert);

    FW::Core::MeshPtr mesh = std::make_shared<FW::Core::Mesh>(
        vertex_data, std::vector<uint>{0, 1, 2, 1, 2, 3});
    FW::Render::RendererMesh mesh_render(mesh);

    FW::Render::Backend::AssetContextParams params;
    params.prealloc = 5;
    uint context = server.new_asset_context(params).get();

    FW::Render::Backend::DrawCommand cmd;
    cmd.type = FW::Render::Backend::DRAW_COMMAND_BEGIN;

    FW::Core::Texture tex;

    tex.reload();

    while (!server.check_close())
    {
        server.poll_events();
        server.add_to_opaque_drawlist(cmd);
        mesh_render.queue_render();
        server.set_done();
    }

    return 0;
}