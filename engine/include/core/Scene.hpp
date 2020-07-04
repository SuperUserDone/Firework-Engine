#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include "core/Action.hpp"
#include "core/objects/Object.hpp"
#include "core/objects/ObjectBasic.hpp"
#include "core/objects/ObjectCamera.hpp"
#include "core/objects/ObjectLight.hpp"
#include "ui/UIIncludes.hpp"

namespace FW
{
namespace Core
{

class Scene;

typedef std::shared_ptr<Scene> ScenePtr;

class Scene
{
private:
    // Objects
    std::vector<std::shared_ptr<ObjectBasic>> m_objects;
    std::vector<std::shared_ptr<ObjectLight>> m_lights;
    std::vector<std::shared_ptr<ObjectCamera>> m_cameras;

    // Internal Updating
    void update_lamps();

    // UI and related
    std::vector<std::function<void()>> m_ui_functions;

public:
    Scene();

    // UI and related
    void add_ui_element(const std::function<void()> &func);

    // Add functions
    void add_object(std::shared_ptr<ObjectBasic> obj);
    void add_light(std::shared_ptr<ObjectLight> obj);
    void add_camera(std::shared_ptr<ObjectCamera> obj);

    // Rendering functions
    void render_forward();
    void render_postprocess();
    void render_ui();

    ~Scene();
};

} // namespace Core
} // namespace FW
