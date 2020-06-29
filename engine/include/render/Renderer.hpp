#pragma once

#include <algorithm>
#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "core/Action.hpp"
#include "core/Scene.hpp"
#include "render/RenderPass.hpp"

#define ns_cast(x) std::chrono::duration_cast<std::chrono::nanoseconds>(x)

using Clock = std::chrono::high_resolution_clock;
using namespace std::chrono_literals;

namespace FW
{
namespace Render
{

class Renderer
{
private:
    bool m_running = true;

    // The render pipeline
    std::vector<RenderPass> m_render_pipeline;

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

public:
    Renderer();

    // Pipeline stuff    std::mutex m_lock_async1;
    std::mutex m_lock_async2;
    std::mutex m_lock_async3;
    void add_pipeline_step(RenderPass pass);

    // Rendering
    bool smart_frame(Core::ScenePtr &scene);
    bool frame(Core::ScenePtr &scene);

    ~Renderer();
};

} // namespace Render
} // namespace FW
