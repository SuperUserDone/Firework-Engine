#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace FW
{
namespace Render
{
namespace Backend
{

enum AssetType
{
    ASSET_TYPE_TEXTURE,
    ASSET_TYPE_MODEL,
    ASSET_TYPE_MATERIAL,
    ASSET_TYPE_CONTEXT
};

struct Asset
{
    AssetType type;
    uint value;
};

enum DrawCommandType
{
    DRAW_COMMAND_MODEL,
    DRAW_COMMAND_BEGIN
};

struct ModelDrawCommand
{
    uint model;
    uint material;

    bool use_camera;

    glm::mat4 model_matrix;
    std::vector<glm::mat4> addtional_transforms;
};

union DrawCommandData
{
    ModelDrawCommand model;
};

struct DrawCommand
{
    DrawCommandType type;
    DrawCommandData data;
};

struct TextureCreateParams
{
};

struct ModelCreateParams
{
};

struct MaterialCreateParams
{
};

struct AssetContextParams
{
};

struct CameraParams
{
};

class RenderBase
{
private:
public:
    // Textures
    virtual uint create_texture(const TextureCreateParams &params) = 0;
    virtual void bind_texture(uint slot, uint texture) = 0;
    virtual void delete_texture(uint texture) = 0;

    // Moddles
    virtual uint create_model(const ModelCreateParams &params) = 0;
    virtual void bind_model(uint model) = 0;
    virtual void delete_model(uint model) = 0;

    // Materials
    virtual uint create_material(const MaterialCreateParams &params) = 0;
    virtual void bind_material(uint material) = 0;
    virtual void delete_material(uint material) = 0;

    // Asset Contexts
    virtual uint new_asset_context(const AssetContextParams &params) = 0;
    virtual void delete_asset_context(uint context) = 0;

    // Camera
    virtual void set_camera(const CameraParams &params) = 0;

    // Drawlists
    virtual void add_to_opaque_drawlist(const DrawCommand &command) = 0;
    virtual void add_to_sorted_drawlist(const DrawCommand &command) = 0;

    // Rendering
    virtual void render() = 0;
};

} // namespace Backend
} // namespace Render
} // namespace FW