#pragma once

#include <functional>
#include <memory>

#include "core/components/Component.hpp"
#include "render/MeshRenderer.hpp"
#include "render/Types.hpp"

namespace FW
{
namespace Core
{

class ComponentMesh : public Component,
                      public std::enable_shared_from_this<ComponentMesh>
{
protected:
    Render::MeshRenderer m_renderer;

public:
    ComponentMesh(MeshPtr mesh);

    // Loading
    virtual void load_assets();
    virtual void load_ogl();
    virtual void update_data();

    virtual ComponentType get_type() { return COMPONENT_MESH; }

    // Rendering
    virtual void setup_render();
    virtual void render_forward() const;

    // Updating
    virtual void tick();

    ~ComponentMesh();
};

} // namespace Core
} // namespace FW