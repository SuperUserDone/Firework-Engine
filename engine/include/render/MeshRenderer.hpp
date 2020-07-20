#pragma once

#include <atomic>
#include <vector>

#include <glad/glad.h>

#include "core/mesh/Mesh.hpp"
#include "render/RendererBase.hpp"
#include "render/Types.hpp"

namespace FW
{
namespace Render
{

enum UpdateMode
{
    MODE_FULL,
    MODE_APPEND,
    MODE_RANGE
};

class MeshRenderer : public RendererBase
{
private:
    std::atomic_bool m_is_loaded;
    std::atomic_bool m_changed;

    Core::MeshPtr m_mesh;

    uint VBO;
    uint VAO;
    uint EBO;

public:
    MeshRenderer(Core::MeshPtr mesh);

    virtual void update(const std::vector<Vertex> &data, int mode = MODE_FULL,
                        int begin = 0, int end = 0, bool re_alloc = false);

    // Loading
    virtual void load_ogl() override;
    virtual void update_ogl() override;
    virtual void unload_ogl() override;

    // Rendering
    virtual void render_forward() const override;

    ~MeshRenderer();
};

} // namespace Render
} // namespace FW
