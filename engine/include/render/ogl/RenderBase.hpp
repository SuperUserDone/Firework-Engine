#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "core/misc/Mesh.hpp"
#include "core/misc/Texture.hpp"

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

struct AssetContext
{
    uint id;
    std::vector<Asset> m_assets;
};

enum DrawCommandType
{
    DRAW_COMMAND_MODEL,
    DRAW_COMMAND_BEGIN
};

struct ModelProperties
{
    uint material;

    bool use_camera;

    glm::mat4 model_matrix;
};

struct ModelDrawCommand
{
    uint model;
    ModelProperties props;
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
    uint asset_context;
    uint8_t *data;

    int channels;

    int sizex;
    int sizey;
    int sizez;

    bool gen_mipmaps;

    Core::TextureType type;
    Core::WrapMode wrap;
    Core::TextureScaleFilter scale_min;
    Core::TextureScaleFilter scale_mag;
};

struct ModelCreateParams
{
    uint asset_context;
    Core::Mesh *mesh;
};

struct MaterialCreateParams
{
    uint asset_context;
};

struct AssetContextParams
{
    uint prealloc;
};

struct CameraParams
{
};

class RenderBase
{
private:
public:
    // Callbacks
    virtual void resize_callback(int x, int y) = 0;

    // Textures
    virtual uint create_texture(const TextureCreateParams &params) = 0;
    virtual void bind_texture(uint slot, uint texture) = 0;
    virtual void delete_texture(uint texture) = 0;

    // Moddles
    virtual uint create_model(const ModelCreateParams &params) = 0;
    virtual void set_model_properties(const ModelProperties &props) = 0;
    virtual void draw_model(uint model) = 0;
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
    virtual void clear_drawlists() = 0;

    // Rendering
    virtual void render() = 0;
};

} // namespace Backend
} // namespace Render
} // namespace FW