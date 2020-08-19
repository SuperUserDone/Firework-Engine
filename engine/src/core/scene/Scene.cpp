#include "core/scene/Scene.hpp"

namespace FW
{
namespace Core
{

Scene::Scene() {}

Entity Scene::make_entity(const std::string &name)
{
    Entity ent(m_entt.create(), this);

    ent.add_component<ComponentTransform>();
    ent.add_component<ComponentTag>(name.empty() ? "Entity" : name);

    return ent;
}

Scene::~Scene() {}

} // namespace Core
} // namespace FW