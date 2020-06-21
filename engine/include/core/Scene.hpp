#pragma once

#include <vector>

#include "render/Action.hpp"

namespace FW
{
namespace Core
{

class Scene
{
private:
    std::vector<Render::Action> m_load_actions;
    std::vector<Render::Action> m_update_actions;

public:
    Scene();

    // Processing and actions
    std::vector<Render::Action> get_loadq();
    std::vector<Render::Action> get_updateq();

    // Rendering functions
    void render_forward();
    void render_postprocess();
    void render_ui();

    ~Scene();
};

} // namespace Core
} // namespace FW
