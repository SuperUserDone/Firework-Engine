#pragma once

#include <atomic>
#include <memory>
#include <vector>

#include "core/Action.hpp"
#include "core/components/Component.hpp"
#include "core/objects/Object.hpp"

namespace FW
{
namespace Core
{

class ObjectLight : public Object
{
protected:
    // Loading
    virtual void load_assets();
    virtual void load_ogl();
    virtual void unload();

public:
    ObjectLight();

    // Actions
    virtual Action get_load_action();
    virtual Action get_unload_action();
    virtual Action get_update_action();

    // Checks
    virtual bool should_gpu_update() const;

    // Rendering
    virtual void setup_render();
    virtual void render_forward() const;

    // Updating
    virtual void tick();

    ~ObjectLight();
};

} // namespace Core
} // namespace FW