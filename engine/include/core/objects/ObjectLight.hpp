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
public:
    ObjectLight();

    // Loading
    virtual void load_assets() override;
    virtual void load_ogl() override;
    virtual void unload() override;

    // Rendering
    virtual void setup_render() override;
    virtual void render_forward(bool override_shaders) const override;

    // Updating
    virtual void tick() override;

    ~ObjectLight();
};

} // namespace Core
} // namespace FW