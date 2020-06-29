#pragma once

#include <memory>
#include <string>
#include <vector>

#include "render/Types.hpp"

namespace FW
{
namespace Core
{

class Mesh;

typedef std::shared_ptr<Mesh> MeshPtr;

class Mesh
{
private:
    std::vector<Render::Vertex> m_data;
    std::vector<uint32_t> m_indices;

public:
    Mesh();
    Mesh(const std::vector<Render::Vertex> &data,
         const std::vector<uint32_t> &indices);

    std::vector<Render::Vertex> &get_data();
    std::vector<uint32_t> &get_indices();

    void update_indices(const std::vector<uint32_t> &indices);
    void update_data(const std::vector<Render::Vertex> &data);

    ~Mesh();
};

} // namespace Core
} // namespace FW