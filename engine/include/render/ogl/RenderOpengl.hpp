#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "render/ogl/RenderBase.hpp"

namespace FW
{
namespace Render
{
namespace Backend
{

class RenderOpengl : public RenderBase
{
private:
public:
    RenderOpengl();

    // Textures
    virtual uint create_texture() override;
    virtual void bind_texture(uint slot, uint texture) override;
    virtual void delete_texture(uint texture) override;

    // Moddles
    virtual uint create_model() override;
    virtual void bind_model(uint model) override;
    virtual void delete_vertex_buffer(uint model) override;

    // Materials
    virtual uint create_material() override;
    virtual void bind_material(uint material) override;
    virtual void delete_material(uint material) override;

    // Asset Contexts
    virtual uint new_asset_context() override;
    virtual void bind_asset_context(uint context) override;
    virtual void delete_asset_context(uint context) override;

    // Camera
    virtual void set_camera() override;

    // Drawlists
    virtual void add_to_opaque_drawlist(DrawCommand command) override;
    virtual void add_to_sorted_drawlist(DrawCommand command) override;
    virtual void prune_drawlist() override;

    // Rendering
    virtual void render() override;

    ~RenderOpengl();
};

} // namespace Backend
} // namespace Render
} // namespace FW