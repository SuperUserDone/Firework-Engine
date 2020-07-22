#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <loguru.hpp>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <Tracy.hpp>

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
    virtual uint create_texture(const TextureCreateParams &params) override;
    virtual void bind_texture(uint slot, uint texture) override;
    virtual void delete_texture(uint texture) override;

    // Moddles
    virtual uint create_model(const ModelCreateParams &params) override;
    virtual void bind_model(uint model) override;
    virtual void delete_model(uint model) override;

    // Materials
    virtual uint create_material(const MaterialCreateParams &params) override;
    virtual void bind_material(uint material) override;
    virtual void delete_material(uint material) override;

    // Asset Contexts
    virtual uint new_asset_context(const AssetContextParams &params) override;
    virtual void delete_asset_context(uint context) override;

    // Camera
    virtual void set_camera(const CameraParams &params) override;

    // Drawlists
    virtual void add_to_opaque_drawlist(const DrawCommand &command) override;
    virtual void add_to_sorted_drawlist(const DrawCommand &command) override;

    // Rendering
    virtual void render() override;

    ~RenderOpengl();
};

} // namespace Backend
} // namespace Render
} // namespace FW