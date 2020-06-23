#include "render/Renderer.hpp"

namespace FW
{
namespace Render
{

Renderer::Renderer() { m_hard_timer = m_soft_timer = Clock::now(); }

/*******************************************************************************/

void Renderer::process_queue(int count, std::queue<Core::Action> &queue)
{
    if (!m_lock_update.try_lock())
        return;

    int presize = queue.size();

    if (presize <= 0)
        return;

    if (count > presize)
        count = presize;

    // TODO Make this "Smarter"
    int max_try = 10;

    // PROCESS THEM Q
    while (queue.size() != presize - count)
    {
        if (queue.front().do_action())
            queue.pop();
        else
        {
            queue.push(queue.front());
            queue.pop();
            if (--max_try <= 0)
                break;
        }
    }

    m_lock_update.unlock();
}
/*******************************************************************************/

void Renderer::add_pipeline_step(RenderPass pass)
{
    m_render_pipeline.push_back(pass);
}

/*******************************************************************************/

void Renderer::add_load_action(const Core::Action &action)
{
    std::lock_guard<std::mutex> qlock(m_lock_update);
    m_load_actions.push(action);
}

/*******************************************************************************/

void Renderer::add_update_action(const Core::Action &action)
{
    std::lock_guard<std::mutex> qlock(m_lock_update);
    m_update_actions.push(action);
}

/*******************************************************************************/

bool Renderer::smart_frame(Core::Scene &scene)
{
    // Merge qs
    std::vector<Core::Action> tmp_load = scene.get_loadq();
    std::vector<Core::Action> tmp_update = scene.get_updateq();
    std::vector<Core::Action> tmp_unload = scene.get_unloadq();

    for (auto &&act : tmp_load)
    {
        m_load_actions.push(act);
    }
    for (auto &&act : tmp_update)
    {
        m_update_actions.push(act);
    }
    for (auto &&act : tmp_unload)
    {
        m_unload_actions.push(act);
    }

    // Updates
    // TODO dynamic maxbatch settings
    process_queue(m_max_unload_batch, m_unload_actions);
    process_queue(m_max_load_batch, m_load_actions);
    process_queue(m_max_update_batch, m_update_actions);

    // Continue with normal rendering
    return frame(scene);
}

/*******************************************************************************/

bool Renderer::frame(Core::Scene &scene)
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
                scene.render_forward();
                break;
            case RENDERPASS_POST_PROCESS:
                scene.render_postprocess();
                break;
            case RENDERPASS_UI:
                scene.render_ui();
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

Renderer::~Renderer() {}

} // namespace Render
} // namespace FW