#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace FW
{
namespace Core
{

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uvs;
    glm::vec3 tangent;
};

class Mesh;
typedef std::shared_ptr<Mesh> MeshPtr;

class Mesh
{
private:
    std::vector<Vertex> m_vertex_data;
    std::vector<uint> m_indices;

    bool m_static = true;

public:
    Mesh();

    // Loading
    void load_from_file(const std::string &path);
    void load_from_resource(const std::string &res_path);
    void load_from_vertex_data(const std::vector<Vertex> &data,
                               const std::vector<uint> &index_data);

    // Getters
    std::vector<Vertex> &get_data();
    std::vector<uint> &get_index_data();
    bool is_static() { return m_static; }

    // Opperators
    Vertex &operator[](size_t index);

    ~Mesh();
};

} // namespace Core
} // namespace FW
