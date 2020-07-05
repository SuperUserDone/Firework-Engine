#include "render/Renderer.hpp"

#include "core/ActionQueue.hpp"
#include "core/TimeHelpers.hpp"
#include "ui/ImguiData.hpp"
#include "input/InputWindow.hpp"

#include <Tracy.hpp>
#include <glad/glad.h>

namespace FW
{
namespace Render
{

Renderer::Renderer() { m_hard_timer = m_soft_timer = Core::get_time(); }

/*******************************************************************************/

void Renderer::add_pipeline_step(RenderPass pass)
{
    m_render_pipeline.push_back(pass);
}

/*******************************************************************************/

bool Renderer::smart_frame(Core::ScenePtr &scene)
{
    // Updates
    // ! Q PROCESSING
    Core::ActionQueue &queue = Core::ActionQueue::get_instance();

    queue.digest_sync_low(10);
    queue.digest_sync_med(20);
    queue.digest_sync_top(30);

    // Continue with normal rendering
    return frame(scene);
}

/*******************************************************************************/

bool Renderer::frame(Core::ScenePtr &scene)
{
    bool return_val = false;

    // Clock things
    bool do_anyways = false;
    if (m_fps_target == 0)
        do_anyways = true;
    double interval = 1.0 / m_fps_target;
    double now = Core::get_time();

    if (m_last_frame + interval < now || do_anyways)
    {
        ZoneScopedN("Frame");

        int x, y;
        x = Input::InputWindow::get_window_width();
        y = Input::InputWindow::get_window_height();

        glViewport(0, 0, x, y);
        // Render Passes
        for (auto pass : m_render_pipeline)
        {
            switch (pass)
            {
            case RENDERPASS_FORWARD:
                scene->render_forward(m_forward_buffer->get_handle());
                m_last_buffer = m_forward_buffer;
                break;
            case RENDERPASS_POST_PROCESS:
                m_last_buffer->bind_texture(0);
                scene->render_postprocess(m_postprocess_buffer->get_handle());
                m_last_buffer = m_postprocess_buffer;
                break;
            case RENDERPASS_UI:
                scene->render_ui(m_last_buffer->get_handle());
                break;
            case RENDERPASS_RESET:
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glBindFramebuffer(GL_FRAMEBUFFER,
                                  m_postprocess_buffer->get_handle());
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glBindFramebuffer(GL_FRAMEBUFFER,
                                  m_forward_buffer->get_handle());
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                break;
            case RENDERPASS_DONE:

                break;
            }
        }

        return_val = true;

        // Incement Frame Counters
        m_hard_frame_count++;
        m_soft_frame_count++;
        m_delta_frame_count++;

        // Set frame clock
        m_last_frame = now;
        FrameMark("Frame");
    }

    // Update fps counter
    if (m_last_fps_update + m_fps_update_interval < now)
    {
        double now = Core::get_time();
        m_fps = m_delta_frame_count;
        m_delta_frame_count = 0;

        if (m_min_fps <= 1)
            m_min_fps = m_fps;

        if (m_fps > m_max_fps)
            m_max_fps = m_fps;

        if (m_fps < m_max_fps)
            m_min_fps = m_fps;

        m_last_fps_update = now;
        TracyPlot("FPS", (int64_t)m_fps);
    }
    return return_val;
}

/*******************************************************************************/

Renderer::~Renderer() { m_running = false; }

} // namespace Render
} // namespace FW