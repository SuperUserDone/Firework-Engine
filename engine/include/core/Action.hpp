#pragma once

#include <atomic>
#include <functional>
#include <memory>
#include <queue>
#include <thread>
#include <vector>

namespace FW
{
namespace Core
{

class Action;

typedef std::shared_ptr<Action> ActionPtr;
typedef std::vector<ActionPtr> ActionPtrVector;
typedef std::queue<ActionPtr> ActionPtrQueue;
typedef std::function<void()> ActionFun;

class Action
{
private:
    ActionFun m_async;
    ActionFun m_sync;

    std::atomic_bool m_done_async;
    std::atomic_bool m_done_sync;

    void run_async();
    void run_sync();

public:
    Action(ActionFun async, ActionFun sync);

    static ActionPtr new_action(ActionFun async, ActionFun sync)
    {
        return std::make_shared<Action>(async, sync);
    }

    void do_async();
    bool try_sync();

    ~Action();
};

} // namespace Core
} // namespace FW
