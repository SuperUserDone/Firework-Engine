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

struct DrawCommand
{
    uint model;
    uint material;

    bool use_camera;

    glm::mat4 model_matrix;
    std::vector<glm::mat4> addtional_transforms;
};

class RenderBase
{
private:
public:
    RenderBase();

    // Textures
    virtual uint create_texture() = 0;
    virtual void bind_texture(uint slot, uint texture) = 0;
    virtual void delete_texture(uint texture) = 0;

    // Moddles
    virtual uint create_model() = 0;
    virtual void bind_model(uint model) = 0;
    virtual void delete_vertex_buffer(uint model) = 0;

    // Materials
    virtual uint create_material() = 0;
    virtual void bind_material(uint material) = 0;
    virtual void delete_material(uint material) = 0;

    // Asset Contexts
    virtual uint new_asset_context() = 0;
    virtual void bind_asset_context(uint context) = 0;
    virtual void delete_asset_context(uint context) = 0;

    // Camera
    virtual void set_camera() = 0;

    // Drawlists
    virtual void add_to_opaque_drawlist(DrawCommand command) = 0;
    virtual void add_to_sorted_drawlist(DrawCommand command) = 0;
    virtual void prune_drawlist() = 0;

    // Rendering
    virtual void render() = 0;

    ~RenderBase();
};

} // namespace Backend
} // namespace Render
} // namespace FW