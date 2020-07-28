#include "core/misc/Mesh.hpp"

namespace FW
{
namespace Core
{

Mesh::Mesh() {}

void Mesh::load_from_file(const std::string &path) {}

void Mesh::load_from_resource(const std::string &res_path) {}

void Mesh::load_from_vertex_data(const std::vector<Vertex> &data,
                                 const std::vector<uint> &index_data)
{
    m_vertex_data = data;
    m_indices = index_data;
}

std::vector<Vertex> &Mesh::get_data() { return m_vertex_data; }

std::vector<uint> &Mesh::get_index_data() { return m_indices; }

Vertex &Mesh::operator[](size_t index) { return m_vertex_data[index]; }

Mesh::~Mesh() {}

} // namespace  Core
} // namespace FW