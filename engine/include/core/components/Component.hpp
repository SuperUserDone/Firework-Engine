#pragma once

#include <atomic>
#include <memory>

namespace FW
{
namespace Core
{

class Object;

class Component : public std::enable_shared_from_this<Component>
{
protected:
    // Loading and related
    std::atomic_bool m_is_loaded;

    // Props
    bool m_is_static = false;
    bool m_changed = false;

    // Parent
    std::shared_ptr<Object> m_parent;

public:
    Component();

    // Loading
    virtual void load_assets() = 0;
    virtual void load_ogl() = 0;
    virtual void update_data() = 0;

    // Checks
    virtual bool is_loaded() const;

    // Rendering
    virtual void setup_render() = 0;
    virtual void render_forward() const = 0;

    // Updating
    virtual void tick() = 0;

    // Parenting
    virtual void set_parent(std::shared_ptr<Object> parent);

    ~Component();
};

} // namespace Core
} // namespace FW
