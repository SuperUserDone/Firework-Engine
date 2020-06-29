#pragma once

#include <string>

#include "core/Scene.hpp"

namespace FW
{
namespace Core
{

class AssetManager
{
private:
public:
    AssetManager();

    void load_bundle(const std::string &path);
    void unload_bundle(const std::string &name);

    ScenePtr load_scene(const std::string &path);
    void unload_scene(ScenePtr scene);
    void save_scene(const std::string &path, ScenePtr scene);

    ~AssetManager();
};

} // namespace Core
} // namespace FW