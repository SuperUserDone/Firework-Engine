#include "render/ogl/RenderDummy.hpp"

namespace FW
{
namespace Render
{
namespace Backend
{

RenderDummy::RenderDummy() {}

uint RenderDummy::create_texture() { return 0; }

void RenderDummy::bind_texture(uint slot, uint texture) {}

void RenderDummy::delete_texture(uint texture) {}

uint RenderDummy::create_model() { return 0; }

void RenderDummy::bind_model(uint model) {}

void RenderDummy::delete_vertex_buffer(uint model) {}

uint RenderDummy::create_material() { return 0; }

void RenderDummy::bind_material(uint material) {}

void RenderDummy::delete_material(uint material) {}

uint RenderDummy::new_asset_context() { return 0; }

void RenderDummy::bind_asset_context(uint context) {}

void RenderDummy::delete_asset_context(uint context) {}

void RenderDummy::set_camera() {}

void RenderDummy::add_to_sorted_drawlist(DrawCommand command) {}

void RenderDummy::add_to_opaque_drawlist(DrawCommand command) {}

void RenderDummy::prune_drawlist() {}

void RenderDummy::render() {}

} // namespace Backend
} // namespace Render
} // namespace FW