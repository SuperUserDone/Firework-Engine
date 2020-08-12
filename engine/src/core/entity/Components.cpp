#include "core/entity/Components.hpp"

namespace FW
{
namespace Core
{

ComponentTransform::ComponentTransform(const glm::vec3 &pos,
                                       const glm::vec3 &rot,
                                       const glm::vec3 &scale)
    : m_pos(pos), m_scale(scale), m_rot(glm::quat(rot))
{
}

ComponentTransform::ComponentTransform(const glm::vec3 &pos,
                                       const glm::quat &rot,
                                       const glm::vec3 &scale)
    : m_pos(pos), m_scale(scale), m_rot(rot)
{
}

ComponentTransform::ComponentTransform(const glm::vec3 &pos) : m_pos(pos)
{
}

ComponentTransform::ComponentTransform(const glm::mat4 &transform)
{
    glm::vec3 s;
    glm::vec4 p;

    glm::decompose(transform, m_scale, m_rot, m_pos, s, p);
}

ComponentTransform::operator glm::mat4() const
{
    glm::mat4 transform = glm::translate(glm::mat4(1.f), m_pos);
    transform = glm::scale(transform, m_scale);
    transform *= glm::toMat4(m_rot);

    return transform;
}

} // namespace Core
} // namespace FW