#pragma once

#include <atomic>
#include <memory>
#include <vector>

#include "core/Action.hpp"
#include "core/components/Component.hpp"

namespace FW
{
namespace Core
{

class Object
{
protected:
    // Components
    std::vector<std::shared_ptr<Component>> m_components;

    // Loading and related
    std::atomic_bool m_loaded;
    bool m_is_static = false;
    bool m_changed = false;

    // Lodading and related
    virtual void load_assets() = 0;
    virtual void load_ogl() = 0;
    virtual void unload() = 0;

public:
    Object();

    // Actions
    virtual Action get_load_action() = 0;
    virtual Action get_unload_action() = 0;
    virtual Action get_update_action() = 0;

    // Components
    virtual void add_component(std::shared_ptr<Component> comp);

    // Checks
    virtual bool is_loaded() const;
    virtual bool should_gpu_update() const = 0;

    // Rendering
    virtual void setup_render() = 0;
    virtual void render_forward() const = 0;

    // Updating
    virtual void tick() = 0;

    ~Object();
};
} // namespace Core
} // namespace FW
