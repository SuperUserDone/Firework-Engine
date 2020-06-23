#pragma once

#include <algorithm>
#include <vector>

#include "core/Action.hpp"
#include "core/objects/Object.hpp"
#include "core/objects/ObjectBasic.hpp"
#include "core/objects/ObjectCamera.hpp"
#include "core/objects/ObjectLight.hpp"

namespace FW
{
namespace Core
{

class Scene
{
private:
    // Action qs
    std::vector<Action> m_load_actions;
    std::vector<Action> m_unload_actions;
    std::vector<Action> m_update_actions;

    // Objects
    std::vector<std::shared_ptr<ObjectBasic>> m_objects;
    std::vector<std::shared_ptr<ObjectLight>> m_lights;
    std::vector<std::shared_ptr<ObjectCamera>> m_cameras;

    // Internal Updating
    void update_lamps();

public:
    Scene();

    // Processing and actions
    std::vector<Action> get_loadq();
    std::vector<Action> get_unloadq();
    std::vector<Action> get_updateq();

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
