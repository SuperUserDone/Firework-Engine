#pragma once

#include "core/components/Component.hpp"

namespace FW
{
namespace Core
{

class ComponentMesh : public Component
{
protected:
public:
    ComponentMesh();

    // Loading
    virtual void load_assets();
    virtual void load_ogl();
    virtual void update_data();

    // Checks
    virtual bool should_update() const;

    // Rendering
    virtual void setup_render();
    virtual void render_forward() const;

    // Updating
    virtual void tick() const;

    ~ComponentMesh();
};

} // namespace Core
} // namespace FW