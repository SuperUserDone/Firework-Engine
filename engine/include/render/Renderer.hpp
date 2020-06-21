#pragma once

#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "core/Scene.hpp"
#include "render/Action.hpp"
#include "render/RenderPass.hpp"

using Clock = std::chrono::high_resolution_clock;
using namespace std::chrono_literals;

namespace FW
{
namespace Render
{

class Renderer
{
private:
    // Locks
    std::mutex m_lock_load;
    std::mutex m_lock_update;

    // Queue for backend opengl stuff
    std::queue<Action> m_load_actions;
    std::queue<Action> m_update_actions;

    // The render pipeline
    std::vector<RenderPass> m_render_pipeline;

    // The max no. of actions to be performed
    uint16_t m_max_load_batch = 10;
    uint16_t m_max_update_batch = 400;

    // FPS stuff
    uint32_t m_fps_target = 120;
    uint32_t m_fps = 0;
    uint32_t m_min_fps = 0;
    uint32_t m_max_fps = 0;

    // Frame counters
    uint32_t m_hard_frame_count = 0;
    uint32_t m_soft_frame_count = 0;
    uint32_t m_delta_frame_count = 0;

    // Update intervals
    std::chrono::milliseconds m_fps_update_interval = 1s;

    // Past events
    std::chrono::time_point<Clock> m_last_fps_update;
    std::chrono::time_point<Clock> m_last_frame;

    // Timers
    std::chrono::time_point<Clock> m_hard_timer;
    std::chrono::time_point<Clock> m_soft_timer;

    // Opengl backend action process
    void process_updates(int count);
    void process_loads(int count);

public:
    Renderer();

    // Pipeline stuff
    void add_pipeline_step(RenderPass pass);

    // Add to Qs
    void add_load_action(Action &action);
    void add_update_action(Action &action);

    // Rendering
    void smart_frame(Core::Scene &scene);
    bool frame(Core::Scene &scene);

    ~Renderer();
};

} // namespace Render
} // namespace FW
