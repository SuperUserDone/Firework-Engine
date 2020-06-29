#pragma once

#include <string>

#include "core/Scene.hpp"

namespace FW
{
namespace Core
{

class SceneManager
{
private:
public:
    SceneManager();

    void set_config(const std::string &path);

    void load_scene(const std::string &name);
    void unload_scene(const std::string &name);
    void set_active(const std::string &name, bool unload = true);

    ScenePtr get_active_scene();

    ~SceneManager();
};

} // namespace Core
} // namespace FW
