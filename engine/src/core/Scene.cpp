#include "core/Scene.hpp"

namespace FW
{
namespace Core
{

Scene::Scene() {}

/*******************************************************************************/


std::vector<Render::Action> Scene::get_loadq()
{
    auto temp = m_load_actions;
    m_load_actions.clear();
    return temp;
}

/*******************************************************************************/

std::vector<Render::Action> Scene::get_updateq()
{
    auto temp = m_update_actions;
    m_update_actions.clear();
    return temp;
}

/*******************************************************************************/

void Scene::render_forward() {}

/*******************************************************************************/

void Scene::render_postprocess() {}

/*******************************************************************************/

void Scene::render_ui() {}

/*******************************************************************************/

Scene::~Scene() {}

} // namespace Core
} // namespace FW