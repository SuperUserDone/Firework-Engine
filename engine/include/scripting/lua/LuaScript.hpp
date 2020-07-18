#pragma once

#include <memory>
#include <string>

#include "scripting/lua/LuaState.hpp"

namespace FW
{
namespace Scripting
{

class LuaScript
{
private:
    std::shared_ptr<sol::environment> m_env;

public:
    LuaScript();

    void load_script(const std::string &path);

    void render_forward();
    void render_ui();

    void tick();

    ~LuaScript();
};

} // namespace Scripting
} // namespace FW
