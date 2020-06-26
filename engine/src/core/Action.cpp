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

void Action::do_async()
{
    if(!m_done_async)
        run_async();
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