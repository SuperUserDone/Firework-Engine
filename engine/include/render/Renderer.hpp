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
    // Locks
    std::mutex m_lock_sync;

    bool m_running = true;

    // The render pipeline
    std::vector<RenderPass> m_render_pipeline;

    // Queue for backend opengl stuff
    std::queue<Core::Action> m_load_actions;
    std::queue<Core::Action> m_unload_actions;
    std::queue<Core::Action> m_update_actions;

    // Loading and syncing
    std::vector<std::shared_ptr<std::mutex>> m_worker_locks;
    std::vector<std::queue<Core::Action>> m_worker_qs;
    std::vector<std::thread> m_async_workers;
    std::vector<bool> m_active;

    // Caps
    uint16_t m_max_load_batch = 10;
    uint16_t m_max_unload_batch = 400;
    uint16_t m_max_update_batch = 400;
    uint8_t m_max_worker_cap = 4;

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
    void process_queue(int count, std::queue<Core::Action> &queue);
    void queue_async(Core::Action &action);

    void async_worker(std::queue<Core::Action> &queue, int index);

public:
    Renderer();

    // Pipeline stuff    std::mutex m_lock_async1;
    std::mutex m_lock_async2;
    std::mutex m_lock_async3;
    void add_pipeline_step(RenderPass pass);

    // Add to Qs
    void add_load_action(const Core::Action &action);
    void add_update_action(const Core::Action &action);

    // Rendering
    bool smart_frame(Core::Scene &scene);
    bool frame(Core::Scene &scene);

    ~Renderer();
};

} // namespace Render
} // namespace FW
