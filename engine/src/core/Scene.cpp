#include "core/Scene.hpp"

namespace FW
{
namespace Core
{

void Scene::update_lamps() {}

/*******************************************************************************/

Scene::Scene() {}

/*******************************************************************************/

std::vector<Action> Scene::get_loadq()
{
    auto temp = m_load_actions;
    m_load_actions.clear();
    return temp;
}

/*******************************************************************************/

std::vector<Action> Scene::get_updateq()
{
    auto temp = m_update_actions;
    m_update_actions.clear();
    return temp;
}

std::vector<Action> Scene::get_unloadq()
{
    auto temp = m_unload_actions;
    m_unload_actions.clear();
    return temp;
}

/*******************************************************************************/

void Scene::render_forward()
{
    if (!m_cameras.empty())
        m_cameras.front()->setup_render();

    bool lamps_update = false;

    std::for_each(std::begin(m_lights), std::end(m_lights),
                  [lamps_update](std::shared_ptr<ObjectLight> obj) {
                      lamps_update | obj->should_gpu_update();
                  });

    if (lamps_update)
        update_lamps();

    std::for_each(std::begin(m_objects), std::end(m_objects),
                  [](std::shared_ptr<ObjectBasic> obj) {
                      obj->setup_render();
                      obj->render_forward();
                  });
} // namespace Core

/*******************************************************************************/

void Scene::render_postprocess() {}

/*******************************************************************************/

void Scene::render_ui() {}

/*******************************************************************************/

Scene::~Scene() {}

} // namespace Core
} // namespace FW