#include "core/Action.hpp"

namespace FW
{
namespace Core
{

Action::Action(std::function<void()> async, std::function<void()> sync)
    : m_async(async), m_sync(sync)
{
}

/*******************************************************************************/

Action::Action(const Action &old)
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

bool Action::try_async()
{
    run_async();

    return true;
}

/*******************************************************************************/

bool Action::try_sync()
{
    if (!m_done_async)
        return false;

    run_sync();

    return true;
}

/*******************************************************************************/

Action::~Action() {}

} // namespace Core
} // namespace FW