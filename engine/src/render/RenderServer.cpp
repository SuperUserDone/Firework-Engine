#include "render/RenderServer.hpp"
#include <chrono>

namespace FW
{
namespace Render
{

void RenderServer::init_renderer(RendererBackend backend)
{
    switch (backend)
    {
    case RENDER_BACKEND_OPENGL43:
        m_render_backend = std::make_unique<Backend::RenderOpengl>();
        break;

    default:
        m_render_backend = std::make_unique<Backend::RenderDummy>();
        break;
    }
    m_render_backend_type = backend;
}

void RenderServer::process_action()
{
    Action act;

    if (!m_action_queue.try_dequeue(act))
        return;

    uint value = 0;

    switch (act.type)
    {
    case ACTION_TYPE_CREATE_TEXTURE:
        value = m_render_backend->create_texture(act.data.texture);
        break;

    case ACTION_TYPE_CREATE_MODEL:
        value = m_render_backend->create_model(act.data.model);
        break;

    case ACTION_TYPE_CREATE_MATERIAL:
        value = m_render_backend->create_material(act.data.material);
        break;

    case ACTION_TYPE_CREATE_ASSET_CONTEXT:
        value = m_render_backend->new_asset_context(act.data.asset_context);
        break;

    case ACTION_TYPE_DELETE_TEXTURE:
        m_render_backend->delete_texture(act.data.id);
        break;

    case ACTION_TYPE_DELETE_MATERIAL:
        m_render_backend->delete_material(act.data.id);
        break;

    case ACTION_TYPE_DELETE_MODEL:
        m_render_backend->delete_model(act.data.id);
        break;

    case ACTION_TYPE_DELETE_ASSET_CONTEXT:
        m_render_backend->delete_asset_context(act.data.id);
        break;

    default:
        break;
    }

    act.output->set_value(value);
}

void RenderServer::render_thread(RendererBackend backend)
{
    using namespace std::chrono_literals;
    m_window.make_window();
    m_window.make_current();
    init_renderer(backend);
    m_init_promise.set_value();

    m_running = true;
    while (m_running)
    {
        m_queue_done = false;
        while (!m_queue_done)
            process_action();

        m_render_backend->render();
        m_window.swap_buffers();
    }
}

RenderServer::RenderServer(const Window::WindowSettings &win,
                           RendererBackend backend)
    : m_window(win)
{
    m_init_promise = std::promise<void>();
    m_init_future = m_init_promise.get_future();

    m_render_thread =
        std::thread(std::bind(&RenderServer::render_thread, this, backend));

    m_init_future.wait();
}

std::future<uint>
RenderServer::create_texture(const Backend::TextureCreateParams &params)
{
    Action act;

    act.type = ACTION_TYPE_CREATE_TEXTURE;
    act.data.texture = params;

    m_action_queue.enqueue(act);

    return act.output->get_future();
}

void RenderServer::delete_texture(uint texture)
{
    Action act;

    act.type = ACTION_TYPE_DELETE_TEXTURE;
    act.data.id = texture;

    m_action_queue.enqueue(act);
}

std::future<uint>
RenderServer::create_model(const Backend::ModelCreateParams &params)
{
    Action act;

    act.type = ACTION_TYPE_CREATE_MODEL;
    act.data.model = params;

    m_action_queue.enqueue(act);

    return act.output->get_future();
}

void RenderServer::delete_model(uint model)
{
    Action act;

    act.type = ACTION_TYPE_DELETE_MODEL;
    act.data.id = model;

    m_action_queue.enqueue(act);
}

std::future<uint>
RenderServer::create_material(const Backend::MaterialCreateParams &params)
{
    Action act;

    act.type = ACTION_TYPE_CREATE_MATERIAL;
    act.data.material = params;

    m_action_queue.enqueue(act);

    return act.output->get_future();
}

void RenderServer::delete_material(uint material)
{
    Action act;

    act.type = ACTION_TYPE_DELETE_MATERIAL;
    act.data.id = material;

    m_action_queue.enqueue(act);
}

std::future<uint>
RenderServer::new_asset_context(const Backend::AssetContextParams &params)
{
    Action act;

    act.type = ACTION_TYPE_CREATE_ASSET_CONTEXT;
    act.data.asset_context = params;

    m_action_queue.enqueue(act);

    return act.output->get_future();
}

void RenderServer::delete_asset_context(uint context)
{
    Action act;

    act.type = ACTION_TYPE_DELETE_ASSET_CONTEXT;
    act.data.id = context;

    m_action_queue.enqueue(act);
}

void RenderServer::set_done() { m_queue_done = true; }

void RenderServer::set_camera(const Backend::CameraParams &params)
{
    m_render_backend->set_camera(params);
}

void RenderServer::add_to_opaque_drawlist(const Backend::DrawCommand &command)
{
    if (command.type == Backend::DRAW_COMMAND_BEGIN)
    {
        while (m_queue_done)
        {
        }
        m_render_backend->clear_drawlists();
    }
    m_render_backend->add_to_opaque_drawlist(command);
}

void RenderServer::add_to_sorted_drawlist(const Backend::DrawCommand &command)
{
    if (command.type == Backend::DRAW_COMMAND_BEGIN)
    {
        while (m_queue_done)
        {
        }
        m_render_backend->clear_drawlists();
    }
    m_render_backend->add_to_sorted_drawlist(command);
}

RenderServer::~RenderServer()
{
    m_running = false;
    m_queue_done = true;
    m_render_thread.join();
}

} // namespace Render
} // namespace FW