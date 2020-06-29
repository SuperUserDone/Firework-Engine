#include "render/Renderer.hpp"

#include "core/ActionQueue.hpp"

#include <glad/glad.h>

namespace FW
{
namespace Render
{

Renderer::Renderer() { m_hard_timer = m_soft_timer = Clock::now(); }

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
    std::chrono::nanoseconds interval = ns_cast(1s) / m_fps_target;
    auto now = Clock::now();

    // Check if frame must be renderered
    if (m_last_frame + interval < now)
    {
        // Render Passes
        for (auto pass : m_render_pipeline)
        {
            switch (pass)
            {
            case RENDERPASS_FORWARD:
                scene->render_forward();
                break;
            case RENDERPASS_POST_PROCESS:
                scene->render_postprocess();
                break;
            case RENDERPASS_UI:
                scene->render_ui();
                break;
            case RENDERPASS_RESET:
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                break;
            }
        }

        return_val = true;

        // Incement Frame Counters
        m_hard_frame_count++;
        m_soft_frame_count++;
        m_delta_frame_count++;

        // Set frame clock
        m_last_frame = Clock::now();
    }

    // Update fps counter
    if (m_last_fps_update + m_fps_update_interval < now)
    {
        m_fps = m_delta_frame_count * (1000 / m_fps_update_interval.count());
        m_delta_frame_count = 0;

        if (m_min_fps <= 1)
            m_min_fps = m_fps;

        if (m_fps > m_max_fps)
            m_max_fps = m_fps;

        if (m_fps < m_max_fps)
            m_min_fps = m_fps;

        m_last_fps_update = Clock::now();
    }
    return return_val;
}

/*******************************************************************************/

Renderer::~Renderer() { m_running = false; }

} // namespace Render
} // namespace FW