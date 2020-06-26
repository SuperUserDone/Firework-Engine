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

class Object : public std::enable_shared_from_this<Object>
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


    // Components
    virtual void add_component(std::shared_ptr<Component> comp);

    // Checks
    virtual bool is_loaded() const;

    // Rendering
    virtual void setup_render() = 0;
    virtual void render_forward() const = 0;

    // Updating
    virtual void tick() = 0;

    ~Object();
};
} // namespace Core
} // namespace FW
