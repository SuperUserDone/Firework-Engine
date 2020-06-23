#pragma once

#include <atomic>
#include <functional>
#include <thread>

namespace FW
{
namespace Core
{

class Action
{
private:
    std::function<void()> m_async;
    std::function<void()> m_sync;

    std::atomic_bool m_done_async;
    std::atomic_bool m_done_sync;

    void run_async();
    void run_sync();

    std::thread async_thread;

public:
    Action(const Action &old);

    Action(std::function<void()> async, std::function<void()> sync);

    bool do_action();

    ~Action();
};

} // namespace Core
} // namespace FW