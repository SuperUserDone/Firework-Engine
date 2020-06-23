#pragma once

#include <atomic>
#include <memory>

namespace FW
{
namespace Core
{

class Component
{
protected:
    // Loading and related
    std::atomic_bool m_is_loaded;

    // Props
    bool m_is_static = false;
    bool m_changed = false;

public:
    Component();

    // Loading
    virtual void load_assets() = 0;
    virtual void load_ogl() = 0;
    virtual void update_data() = 0;

    // Checks
    virtual bool is_loaded() const;
    virtual bool should_update() const = 0;

    // Rendering
    virtual void setup_render() = 0;
    virtual void render_forward() const = 0;

    // Updating
    virtual void tick() const = 0;

    ~Component();
};

} // namespace Core
} // namespace FW
