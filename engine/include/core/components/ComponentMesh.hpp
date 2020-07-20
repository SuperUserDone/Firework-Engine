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
    Render::RendererBasePtr m_renderer;

public:
    ComponentMesh(MeshPtr mesh);

    // Getters
    virtual ComponentType get_type() override { return COMPONENT_MESH; }
    virtual Render::RendererBasePtr get_renderer();

    // Setters
    virtual void set_renderer(Render::RendererBasePtr renderer);

    // Loading
    virtual void load_assets() override;
    virtual void load_ogl() override;
    virtual void update_data() override;

    // Rendering
    virtual void setup_render() override;
    virtual void render_forward(bool override_shaders) const override;

    // Updating
    virtual void tick() override;

    ~ComponentMesh();
};

} // namespace Core
} // namespace FW