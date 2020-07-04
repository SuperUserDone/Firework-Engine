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
    double m_fps_update_interval = 1;

    // Past events
    double m_last_fps_update;
    double m_last_frame;

    // Timers
    double m_hard_timer;
    double m_soft_timer;

    FramebufferPtr m_forward_buffer;
    FramebufferPtr m_postprocess_buffer;
    FramebufferPtr m_last_buffer;

public:
    Renderer();

    void set_forward_buffer(FramebufferPtr b) { m_forward_buffer = b; }
    void set_postprocess_buffer(FramebufferPtr b) { m_postprocess_buffer = b; }
    void set_last_buffer();

    // Pipeline stuff
    void add_pipeline_step(RenderPass pass);

    // Rendering
    bool smart_frame(Core::ScenePtr &scene);
    bool frame(Core::ScenePtr &scene);

    ~Renderer();
};

} // namespace Render
} // namespace FW
