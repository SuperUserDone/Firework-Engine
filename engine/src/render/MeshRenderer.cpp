#include "render/MeshRenderer.hpp"

namespace FW
{
namespace Render
{

MeshRenderer::MeshRenderer(Core::MeshPtr mesh) : m_mesh(mesh) {}

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_mesh->get_data().size(),
                 &m_mesh->get_data()[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 m_mesh->get_indices().size() * sizeof(uint32_t),
                 &m_mesh->get_indices()[0], GL_STATIC_DRAW);

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
                          (void *)offsetof(Vertex, uv_color));

    // Tangents
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, tangent));
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void *)offsetof(Vertex, bitangent));

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
    glDrawElements(GL_TRIANGLES, m_mesh->get_indices().size(), GL_UNSIGNED_INT,
                   0);
}

/*******************************************************************************/

MeshRenderer::~MeshRenderer() {}

} // namespace Render
} // namespace FW