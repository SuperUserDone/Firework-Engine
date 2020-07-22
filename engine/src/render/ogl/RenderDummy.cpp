#include "render/ogl/RenderDummy.hpp"

namespace FW
{
namespace Render
{
namespace Backend
{

RenderDummy::RenderDummy() {}

uint RenderDummy::create_texture(const TextureCreateParams &params)
{
    return 0;
}

void RenderDummy::bind_texture(uint slot, uint texture) {}

void RenderDummy::delete_texture(uint texture) {}

uint RenderDummy::create_model(const ModelCreateParams &params) { return 0; }

void RenderDummy::bind_model(uint model) {}

void RenderDummy::delete_model(uint model) {}

uint RenderDummy::create_material(const MaterialCreateParams &params)
{
    return 0;
}

void RenderDummy::bind_material(uint material) {}

void RenderDummy::delete_material(uint material) {}

uint RenderDummy::new_asset_context(const AssetContextParams &params)
{
    return 0;
}

void RenderDummy::delete_asset_context(uint context) {}

void RenderDummy::set_camera(const CameraParams &params) {}

void RenderDummy::add_to_sorted_drawlist(const DrawCommand &command) {}

void RenderDummy::add_to_opaque_drawlist(const DrawCommand &command) {}

void RenderDummy::render() {}

RenderDummy::~RenderDummy() {}

} // namespace Backend
} // namespace Render
} // namespace FW