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

    // Rendering
    virtual void setup_render();
    virtual void render_forward() const;

    // Updating
    virtual void tick();

    ~ObjectLight();
};

} // namespace Core
} // namespace FW