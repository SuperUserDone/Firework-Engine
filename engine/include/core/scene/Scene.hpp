#pragma once

#include "core/entity/Components.hpp"

#include "entt/entt.hpp"

namespace FW
{
namespace Core
{

class Entity;

class Scene
{
private:
    entt::registry m_entt;

public:
    Scene();

    Entity make_entity(const std::string &name = "");

    ~Scene();

    friend class Entity;
};

class Entity
{
private:
    std::optional<entt::entity> m_id;

    Scene *m_scene;

public:
    Entity(entt::entity id, Scene *scene) : m_id(id), m_scene(scene) {}

    template <typename T, typename... Args>
    T &add_component(Args &&... args)
    {
        if (!m_scene)
            throw std::runtime_error("Could not add component! Scene is null? "
                                     "This should not happen!");
        if (has_component<T>())
            throw std::runtime_error(
                "Could not add component! Component exists!");

        if (!m_id.has_value())
            throw std::runtime_error(
                "Could not add component! Entity does not exist in registry!");

        return m_scene->m_entt.emplace<T>(m_id.value(),
                                          std::forward<Args>(args)...);
    }
    template <typename T>
    bool has_component()
    {
        if (!m_id.has_value())
            throw std::runtime_error(
                "could not check for componenet in entity! Entity does not "
                "exist in registry!");

        return m_scene->m_entt.has<T>(m_id.value());
    }
    template <typename T>
    void remove_component()
    {
        if (!m_id.has_value())
            throw std::runtime_error(
                "Could remove componenet in entity! Entity does not "
                "exist in registry!");

        return m_scene->m_entt.remove_if_exists<T>(m_id.value());
    }
    template <typename T>
    T &get_component()
    {
        if (has_component<T>())
            throw std::runtime_error(
                "Could not get component! Entity does not have component!");
        if (!m_id.has_value())
            throw std::runtime_error(
                "Could get componenet in entity! Entity does not "
                "exist in registry!");

        m_scene->m_entt.get<T>(m_id.value());
    }
};

} // namespace Core
} // namespace FW