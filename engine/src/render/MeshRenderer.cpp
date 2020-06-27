#include "render/MeshRenderer.hpp"

namespace FW
{
namespace Render
{

MeshRenderer::MeshRenderer(const std::vector<Vertex> &data,
                           std::vector<uint32_t> &indices)
    : m_data(data), m_indices(indices)
{
}

/*******************************************************************************/

void MeshRenderer::update(const std::vector<Vertex> &data, int mode, int begin,
                          int end, bool re_alloc)
{
}

/*******************************************************************************/

void MeshRenderer::load_ogl()
{
    // Buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Load Vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_data.size(), &m_data[0],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(uint32_t),
                 &m_indices[0], GL_STATIC_DRAW);

    // Attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, uv));

    // glBindVertexArray(0);
    m_is_loaded = true;
}

/*******************************************************************************/

void MeshRenderer::update_ogl() {}

/*******************************************************************************/

void MeshRenderer::unload_ogl() {}

/*******************************************************************************/

void MeshRenderer::render_forward() const
{
    if (!m_is_loaded)
        return;

    // Arrays
    glBindVertexArray(VAO);
    // Draw
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
}

/*******************************************************************************/

MeshRenderer::~MeshRenderer() {}

} // namespace Render
} // namespace FW