#include "render/Renderer.hpp"

namespace FW
{
namespace Render
{

Renderer::Renderer() { m_hard_timer = m_soft_timer = Clock::now(); }

/*******************************************************************************/

void Renderer::process_updates(int count)
{
    if (!m_lock_update.try_lock())
        return;

    int presize = m_update_actions.size();

    if (presize <= 0)
        return;

    if (count > presize)
        count = presize;

    // TODO Make this "Smarter"
    int max_try = 10;

    // PROCESS THEM Q
    while (m_update_actions.size() != presize - count)
    {
        if (m_update_actions.front().do_action())
            m_update_actions.pop();
        else
        {
            m_update_actions.push(m_update_actions.front());
            m_update_actions.pop();
            if (--max_try <= 0)
                break;
        }
    }

    m_lock_update.unlock();
}

/*******************************************************************************/

void Renderer::process_loads(int count)
{
    if (!m_lock_load.try_lock())
        return;

    int presize = m_load_actions.size();

    if (presize <= 0)
        return;

    if (count > presize)
        count = presize;

    // TODO Make this "Smarter"
    int max_try = 10;

    // PROCESS THEM Q
    while (m_load_actions.size() != presize - count)
    {
        if (m_load_actions.front().do_action())
            m_load_actions.pop();
        else
        {
            m_load_actions.push(m_load_actions.front());
            m_load_actions.pop();
            if (--max_try <= 0)
                break;
        }
    }

    m_lock_load.unlock();
}

/*******************************************************************************/

void Renderer::add_pipeline_step(RenderPass pass)
{
    m_render_pipeline.push_back(pass);
}

/*******************************************************************************/

void Renderer::add_load_action(Action &action)
{
    std::lock_guard<std::mutex> qlock(m_lock_load);
    m_load_actions.push(action);
}

/*******************************************************************************/

void Renderer::add_update_action(Action &action)
{
    std::lock_guard<std::mutex> qlock(m_lock_update);
    m_update_actions.push(action);
}

/*******************************************************************************/

void Renderer::smart_frame(Core::Scene &scene)
{
    // Merge qs
    std::vector<Action> tmp_load = scene.get_loadq();
    std::vector<Action> tmp_update = scene.get_updateq();

    for (auto &&act : tmp_load)
    {
        m_load_actions.push(act);
    }
    for (auto &&act : tmp_update)
    {
        m_update_actions.push(act);
    }

    // Updates
    // TODO dynamic maxbatch settings
    process_loads(m_max_load_batch);
    process_updates(m_max_update_batch);

    // Continue with normal rendering
    frame(scene);
}

/*******************************************************************************/

bool Renderer::frame(Core::Scene &scene)
{
    // Clock things
    auto interval = 1000ms / m_fps_target;
    auto now = Clock::now();

    // Check if frame must be renderered
    if (m_last_frame > now - interval)
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

        // Incement Frame Counters
        m_hard_frame_count++;
        m_soft_frame_count++;
        m_delta_frame_count++;

        // Set frame clock
        m_last_frame = Clock::now();
    }

    // Update fps counter
    if (m_last_fps_update < now - m_fps_update_interval)
    {
        m_fps = m_delta_frame_count * (1000 / m_fps_update_interval.count());
        m_delta_frame_count = 0;

        if (m_min_fps == 0)
            m_min_fps = m_fps;

        if (m_fps > m_max_fps)
            m_max_fps = m_fps;

        if (m_fps < m_max_fps)
            m_min_fps = m_fps;

        m_last_fps_update = Clock::now();
        std::cout << m_fps << std::endl;
    }
    return true;
}

/*******************************************************************************/

Renderer::~Renderer() {}

} // namespace Render
} // namespace FW