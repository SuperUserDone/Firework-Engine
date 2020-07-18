#include "core/ActionQueue.hpp"

#include <Tracy.hpp>
namespace FW
{
namespace Core
{

void ActionQueue::add_low_action(ActionPtr action)
{
    m_action_pool.push(std::bind(&Action::do_async, action.get()));
    std::unique_lock<std::mutex> lock(m_low_lock);
    m_low_prio.push(action);
}

/*******************************************************************************/

void ActionQueue::add_med_action(ActionPtr action)
{
    m_action_pool.push(std::bind(&Action::do_async, action.get()));
    std::unique_lock<std::mutex> lock(m_med_lock);
    m_med_prio.push(action);
}

/*******************************************************************************/

void ActionQueue::add_top_action(ActionPtr action)
{
    m_action_pool.push(std::bind(&Action::do_async, action.get()));
    std::unique_lock<std::mutex> lock(m_top_lock);
    m_top_prio.push(action);
}

/*******************************************************************************/

void ActionQueue::digest_sync_low(int count, int max)
{
    std::unique_lock<std::mutex> lock(m_low_lock);
    digest(m_low_prio, count, max);
}

/*******************************************************************************/

void ActionQueue::digest_sync_med(int count, int max)
{
    std::unique_lock<std::mutex> lock(m_med_lock);
    digest(m_med_prio, count, max);
}

/*******************************************************************************/

void ActionQueue::digest_sync_top(int count, int max)
{
    std::unique_lock<std::mutex> lock(m_top_lock);
    digest(m_top_prio, count, max);
}

/*******************************************************************************/

void ActionQueue::force_all() {}

/*******************************************************************************/

void ActionQueue::digest(ActionPtrQueue &queue, uint count, uint max)
{
    uint presize = queue.size();

    if (presize <= 0)
        return;

    if (count > presize)
        count = presize;

    // TODO Make this "Smarter"
    int max_try = 10;

    // PROCESS THEM Q
    while (queue.size() != presize - count)
    {
        if (queue.front()->try_sync())
            queue.pop();
        else
        {
            queue.push(queue.front());
            queue.pop();
            if (--max_try <= 0)
                break;
        }
    }
}

} // namespace Core
} // namespace FW