
#include "scripting/lua/LuaScript.hpp"

namespace FW
{
namespace Scripting
{

LuaScript::LuaScript() { m_env = LuaState::getInstance().get_enviornment(); }

/*******************************************************************************/

void LuaScript::load_script(const std::string &path) {}

/*******************************************************************************/

void LuaScript::render_forward() {}

/*******************************************************************************/

void LuaScript::render_ui() {}

/*******************************************************************************/

void LuaScript::tick() {}

/*******************************************************************************/

LuaScript::~LuaScript() {}

} // namespace Scripting
} // namespace FW