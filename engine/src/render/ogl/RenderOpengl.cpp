#include "render/ogl/RenderOpengl.hpp"

namespace FW
{
namespace Render
{
namespace Backend
{

RenderOpengl::RenderOpengl() {}
uint RenderOpengl::create_texture(const TextureCreateParams &params)
{
    return 0;
}
void RenderOpengl::bind_texture(uint slot, uint texture) {}

void RenderOpengl::delete_texture(uint texture) {}

uint RenderOpengl::create_model(const ModelCreateParams &params) { return 0; }

void RenderOpengl::bind_model(uint model) {}

void RenderOpengl::delete_vertex_buffer(uint model) {}

uint RenderOpengl::create_material(const MaterialCreateParams &params)
{
    return 0;
}

void RenderOpengl::bind_material(uint material) {}

void RenderOpengl::delete_material(uint material) {}

uint RenderOpengl::new_asset_context(const AssetContextParams &params)
{
    return 0;
}

void RenderOpengl::bind_asset_context(uint context) {}

void RenderOpengl::delete_asset_context(uint context) {}

void RenderOpengl::set_camera() {}

void RenderOpengl::add_to_sorted_drawlist(DrawCommand command) {}

void RenderOpengl::add_to_opaque_drawlist(DrawCommand command) {}

void RenderOpengl::prune_drawlist() {}

void RenderOpengl::render() {}

} // namespace Backend
} // namespace Render
} // namespace FW