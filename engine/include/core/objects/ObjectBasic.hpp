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

class ObjectBasic : public Object
{
protected:
    // Loading
    virtual void load_assets();
    virtual void load_ogl();
    virtual void unload();

public:
    ObjectBasic();

    // Rendering
    virtual void setup_render();
    virtual void render_forward() const;

    // Components

    // Updating
    virtual void tick();

    ~ObjectBasic();
};

} // namespace Core
} // namespace FW