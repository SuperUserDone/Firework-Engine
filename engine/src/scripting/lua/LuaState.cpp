#include "scripting/lua/LuaState.hpp"

namespace FW
{
namespace Scripting
{

LuaState::LuaState() {}

/*******************************************************************************/

std::shared_ptr<sol::environment> LuaState::get_enviornment()
{
    return std::make_shared<sol::environment>(m_state, sol::create,
                                              m_state.globals());
}

/*******************************************************************************/

void LuaState::load_script(const std::string &path)
{
    m_state.script_file(path);
}

/*******************************************************************************/

void LuaState::load_script(const std::string &path,
                           std::shared_ptr<sol::environment> env)
{
    m_state.script_file(path, *env.get());
}

/*******************************************************************************/

LuaState::~LuaState() {}

} // namespace Scripting
} // namespace FW