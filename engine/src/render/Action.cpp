#include "render/Action.hpp"

namespace FW
{
namespace Render
{

Action::Action(std::function<void()> async, std::function<void()> sync)
    : m_async(async), m_sync(sync)
{
    async_thread = std::thread(std::bind(&Action::run_async, this));
    async_thread.detach();
}

/*******************************************************************************/

Action::Action(const FW::Render::Action &old)
{
    m_async = old.m_async;
    m_sync = old.m_sync;

    m_done_async = old.m_done_async.load();
    m_done_sync = old.m_done_sync.load();
}

/*******************************************************************************/

void Action::run_async()
{
    m_async();
    m_done_async = true;
}

/*******************************************************************************/

void Action::run_sync()
{
    m_sync();
    m_done_sync = true;
}

/*******************************************************************************/

bool Action::do_action()
{
    if (!m_done_async)
        return false;

    run_sync();

    return true;
}

/*******************************************************************************/

Action::~Action()
{
    if (async_thread.joinable())
        async_thread.join();
}

} // namespace Render
} // namespace FW