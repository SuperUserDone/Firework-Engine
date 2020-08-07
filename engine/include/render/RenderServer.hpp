#pragma once

#include <atomic>
#include <future>
#include <mutex>
#include <thread>
#include <vector>

#include "concurrentqueue.h"

#include "render/ogl/RenderBase.hpp"
#include "render/ogl/RenderDummy.hpp"
#include "render/ogl/RenderOpengl.hpp"
#include "window/Window.hpp"

namespace FW
{
namespace Render
{

enum RendererBackend
{
    RENDER_BACKEND_DUMMY,
    RENDER_BACKEND_OPENGL43
};

enum ActionType
{
    ACTION_TYPE_CREATE_TEXTURE,
    ACTION_TYPE_CREATE_MODEL,
    ACTION_TYPE_CREATE_MATERIAL,
    ACTION_TYPE_CREATE_ASSET_CONTEXT,
    ACTION_TYPE_DELETE_TEXTURE,
    ACTION_TYPE_DELETE_MODEL,
    ACTION_TYPE_DELETE_MATERIAL,
    ACTION_TYPE_DELETE_ASSET_CONTEXT
};

union ActionData
{
    uint id;
    Backend::TextureCreateParams texture;
    Backend::ModelCreateParams model;
    Backend::MaterialCreateParams material;
    Backend::AssetContextParams asset_context;
};

struct Action
{
    Action() { output = std::make_shared<std::promise<uint>>(); }

    ActionType type;
    ActionData data;
    std::shared_ptr<std::promise<uint>> output;
};

class RenderServer
{
private:
    std::thread m_render_thread;

    std::atomic_bool m_running = false;
    std::atomic_bool m_queue_done;

    std::promise<void> m_init_promise;
    std::future<void> m_init_future;

    RendererBackend m_render_backend_type;
    std::unique_ptr<Backend::RenderBase> m_render_backend;

    moodycamel::ConcurrentQueue<Action> m_action_queue;

    Window::Window m_window;

    void init_renderer(RendererBackend backend);
    void render_thread(RendererBackend backend);

    void process_action();

    RenderServer(RenderServer const &) = delete;
    void operator=(RenderServer const &) = delete;

public:
    RenderServer(const Window::WindowSettings &win,
                 RendererBackend backend = RENDER_BACKEND_OPENGL43);

    static RenderServer &get_instance() { return init({}); }
    static RenderServer &init(const Window::WindowSettings &win,
                              RendererBackend backend = RENDER_BACKEND_OPENGL43)
    {
        static RenderServer instance(win, backend);
        return instance;
    }

    // Meta
    void resize_callback(int x, int y);

    // Textures
    virtual std::future<uint>
    create_texture(const Backend::TextureCreateParams &params);
    virtual void delete_texture(uint texture);

    // Models
    virtual std::future<uint>
    create_model(const Backend::ModelCreateParams &params);
    virtual void delete_model(uint model);

    // Materials
    virtual std::future<uint>
    create_material(const Backend::MaterialCreateParams &params);
    virtual void delete_material(uint material);

    // Asset Contexts
    virtual std::future<uint>
    new_asset_context(const Backend::AssetContextParams &params);
    virtual void delete_asset_context(uint context);
    virtual void set_done();

    // Camera
    virtual void set_camera(const Backend::CameraParams &params);

    // Drawlists
    virtual void add_to_opaque_drawlist(const Backend::DrawCommand &command);
    virtual void add_to_sorted_drawlist(const Backend::DrawCommand &command);

    virtual bool check_close() { return m_window.check_close(); }
    virtual void poll_events() { m_window.poll_events(); }

    ~RenderServer();
};

} // namespace Render
} // namespace FW
