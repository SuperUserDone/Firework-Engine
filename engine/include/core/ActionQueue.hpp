#pragma once

#include <mutex>

#include "core/Action.hpp"
#include "ctpl_stl.h"

namespace FW
{
namespace Core
{

class ActionQueue
{
private:
    // Locks
    std::mutex m_low_lock;
    std::mutex m_med_lock;
    std::mutex m_top_lock;

    // Queue for backend opengl stuff
    ActionPtrQueue m_low_prio;
    ActionPtrQueue m_med_prio;
    ActionPtrQueue m_top_prio;

    // Pool
    ctpl::thread_pool m_action_pool;

    void digest(ActionPtrQueue &queue, uint count, uint max);

public:
    ActionQueue() : m_action_pool(4) {}

    static ActionQueue &get_instance()
    {
        static ActionQueue ins;
        return ins;
    }

    // Add
    void add_low_action(ActionPtr action);
    void add_med_action(ActionPtr action);
    void add_top_action(ActionPtr action);

    // Digest
    void digest_sync_low(int count, int max = 10);
    void digest_sync_med(int count, int max = 20);
    void digest_sync_top(int count, int max = 30);

    // Force
    void force_all();

    ActionQueue(Action const &) = delete;
    void operator=(ActionQueue const &) = delete;
};

} // namespace Core
} // namespace FW