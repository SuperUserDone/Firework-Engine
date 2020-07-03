#include "core/Action.hpp"

#include <Tracy.hpp>

namespace FW
{
namespace Core
{
Action::Action(std::function<void()> async, std::function<void()> sync)
    : m_async(async), m_sync(sync)
{
}

/*******************************************************************************/

void Action::run_async()
{
    ZoneScopedN("Async action");
    if (m_async)
        m_async();
    m_done_async = true;
}

/*******************************************************************************/

void Action::run_sync()
{
    ZoneScopedN("Sync action");
    if (m_sync)
        m_sync();
    m_done_sync = true;
}

/*******************************************************************************/

void Action::do_async()
{
    ZoneScopedN("Action Async attempt");
    if (!m_done_async)
        run_async();
}

/*******************************************************************************/

bool Action::try_sync()
{
    ZoneScopedN("Action Sync attempt");
    if (!m_done_async)
        return false;

    run_sync();

    return true;
}

/*******************************************************************************/

Action::~Action() {}

} // namespace Core
} // namespace FW