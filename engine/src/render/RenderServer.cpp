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

void RenderServer::render_thread(Window::Window *win, RendererBackend backend)
{
    m_window = win;
    using namespace std::chrono_literals;
    win->make_window();
    win->make_current();
    init_renderer(backend);

    m_running = true;
    m_queue_complete_future = m_queue_complete_promise.get_future();
    while (m_running)
    {
        while (m_queue_complete_future.wait_for(1ms) ==
               std::future_status::timeout)
            process_action();

        m_queue_complete_future.get();

        m_render_backend->render();
        m_window->swap_buffers();
        m_queue_complete_promise = std::promise<void>();
        m_queue_complete_future = m_queue_complete_promise.get_future();
        m_frame_lock.unlock();
    }
}

RenderServer::RenderServer(Window::Window *win, RendererBackend backend)
{

    m_render_thread = std::thread(
        std::bind(&RenderServer::render_thread, this, win, backend));
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

void RenderServer::set_done()
{
    m_frame_lock.lock();
    m_queue_complete_promise.set_value();
}

void RenderServer::set_camera(const Backend::CameraParams &params)
{
    m_render_backend->set_camera(params);
}

void RenderServer::add_to_opaque_drawlist(const Backend::DrawCommand &command)
{
    if (command.type == Backend::DRAW_COMMAND_BEGIN)
    {
        std::lock_guard<std::mutex> frame(m_frame_lock);
    }
    m_render_backend->add_to_opaque_drawlist(command);
}

void RenderServer::add_to_sorted_drawlist(const Backend::DrawCommand &command)
{
    if (command.type == Backend::DRAW_COMMAND_BEGIN)
    {
        std::lock_guard<std::mutex> frame(m_frame_lock);
    }
    m_render_backend->add_to_sorted_drawlist(command);
}

RenderServer::~RenderServer()
{
    m_running = false;
    m_frame_lock.lock();
    m_queue_complete_promise.set_value();
    m_render_thread.join();
    m_window->~Window();
}

} // namespace Render
} // namespace FW