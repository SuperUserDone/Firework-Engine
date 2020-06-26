#include "core/Scene.hpp"

namespace FW
{
namespace Core
{

void Scene::update_lamps() {}

/*******************************************************************************/

Scene::Scene() {}

/*******************************************************************************/

void Scene::add_object(std::shared_ptr<ObjectBasic> obj)
{
    m_objects.push_back(obj);
}

/*******************************************************************************/

void Scene::add_light(std::shared_ptr<ObjectLight> obj) {}

/*******************************************************************************/

void Scene::render_forward()
{
    if (!m_cameras.empty())
        m_cameras.front()->setup_render();

    bool lamps_update = false;

    for (auto &&lamp : m_lights)
    {
        // TODO Logic for checking updates
    }

    if (lamps_update)
        update_lamps();

    std::for_each(std::begin(m_objects), std::end(m_objects),
                  [](std::shared_ptr<ObjectBasic> obj) {
                      obj->setup_render();
                      obj->render_forward();
                  });
}

/*******************************************************************************/

void Scene::render_postprocess() {}

/*******************************************************************************/

void Scene::render_ui() {}

/*******************************************************************************/

Scene::~Scene() {}

} // namespace Core
} // namespace FW