#pragma once

#include <mutex>
#include <queue>
#include <string>
#include <unordered_map>
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

struct _Model
{
    uint model_id;
    uint context_id;

    uint data_buffer;
    uint array_buffer;
    uint element_buffer;

    uint index_size;
};

class RenderOpengl : public RenderBase
{
private:
    std::mutex m_render_lock;

    std::vector<DrawCommand> m_opaque_draw;
    std::vector<DrawCommand> m_sorted_draw;

    std::unordered_map<uint, AssetContext> m_asset_contexts;

    std::unordered_map<uint, _Model> m_models;

    uint m_model_id_index = 0;
    uint m_context_id_index = 0;

public:
    RenderOpengl();

    // Textures
    uint create_texture(const TextureCreateParams &params) override;
    void bind_texture(uint slot, uint texture) override;
    void delete_texture(uint texture) override;

    // Moddles
    uint create_model(const ModelCreateParams &params) override;
    void draw_model(uint model) override;
    void delete_model(uint model) override;

    // Materials
    uint create_material(const MaterialCreateParams &params) override;
    void set_model_properties(const ModelProperties &props) override;
    void bind_material(uint material) override;
    void delete_material(uint material) override;

    // Asset Contexts
    uint new_asset_context(const AssetContextParams &params) override;
    void delete_asset_context(uint context) override;

    // Camera
    void set_camera(const CameraParams &params) override;

    // Drawlists
    void add_to_opaque_drawlist(const DrawCommand &command) override;
    void add_to_sorted_drawlist(const DrawCommand &command) override;
    void clear_drawlists() override;

    // Rendering
    void render() override;

    ~RenderOpengl();
};

} // namespace Backend
} // namespace Render
} // namespace FW