#pragma once

#include <memory>

#define SOL_ALL_SAFETIES_ON 1
#include "sol.hpp"

namespace FW
{
namespace Scripting
{

class LuaState
{
public:
    static LuaState &getInstance()
    {
        static LuaState instance;
        return instance;
    }

private:
    sol::state m_state;

public:
    LuaState();

    std::shared_ptr<sol::environment> get_enviornment();

    void load_script(const std::string &path);
    void load_script(const std::string &path,
                     std::shared_ptr<sol::environment> env);

    ~LuaState();

    void operator=(LuaState const &) = delete;
    LuaState(LuaState const &) = delete;
};

} // namespace Scripting

} // namespace FW
