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
    glm::vec2 uv;
};

} // namespace Render
} // namespace FW