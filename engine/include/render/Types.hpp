#pragma once

#include <glm/glm.hpp>

namespace FW
{
namespace Render
{

struct Vertex
{
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 uv_color;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

} // namespace Render
} // namespace FW