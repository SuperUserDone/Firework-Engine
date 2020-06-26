#pragma once

#include <atomic>
#include <vector>

#include <glad/glad.h>

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

class MeshRenderer
{
private:
    std::atomic_bool m_is_loaded;
    std::atomic_bool m_changed;

    std::vector<Vertex> m_data;
    std::vector<uint32_t> m_indices;

    uint VBO;
    uint VAO;
    uint EBO;

public:
    MeshRenderer(const std::vector<Vertex> &data,
                 std::vector<uint32_t> &indices);

    void update(const std::vector<Vertex> &data, int mode = MODE_FULL,
                int begin = 0, int end = 0, bool re_alloc = false);

    // Loading
    void load_ogl();
    void update_ogl();
    void unload_ogl();

    // Rendering
    void render_forward() const;

    ~MeshRenderer();
};

} // namespace Render
} // namespace FW
