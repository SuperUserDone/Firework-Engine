#include "core/mesh/Mesh.hpp"

namespace FW
{
namespace Core
{

Mesh::Mesh() {}

/*******************************************************************************/

Mesh::Mesh(const std::vector<Render::Vertex> &data,
           const std::vector<uint32_t> &indices)
    : m_data(data), m_indices(indices)
{
}

/*******************************************************************************/

std::vector<Render::Vertex> &Mesh::get_data() { return m_data; }

/*******************************************************************************/

std::vector<uint32_t> &Mesh::get_indices() { return m_indices; }

/*******************************************************************************/

void Mesh::update_indices(const std::vector<uint32_t> &indices)
{
    m_indices = indices;
}

/*******************************************************************************/

void Mesh::update_data(const std::vector<Render::Vertex> &data)
{
    m_data = data;
}

/*******************************************************************************/

Mesh::~Mesh() {}

} // namespace Core
} // namespace FW
