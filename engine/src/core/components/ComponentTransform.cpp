#include "core/components/ComponentTransform.hpp"

namespace FW
{
namespace Core
{

glm::mat4 ComponentTransform::build_matrix() const
{
    glm::mat4 matrix = glm::identity<glm::mat4>();

    matrix = glm::translate(matrix, m_pos);
    matrix = matrix * glm::toMat4(m_rot);
    matrix = glm::scale(matrix, m_scale);
    return matrix;
}

/*******************************************************************************/

ComponentTransform::ComponentTransform()
{
    m_pos = glm::vec3(0, 0, 0);
    m_rot = glm::quat(glm::vec3(0.0, 0.0, 0.0));
    m_scale = glm::vec3(1, 1, 1);
}

/*******************************************************************************/

void ComponentTransform::load_assets() {}

/*******************************************************************************/

void ComponentTransform::load_ogl() {}

/*******************************************************************************/

void ComponentTransform::update_data() {}

/*******************************************************************************/

void ComponentTransform::set_pos(const glm::vec3 &pos) { m_pos = pos; }

/*******************************************************************************/

void ComponentTransform::set_rot(const glm::quat &rot) { m_rot = rot; }

/*******************************************************************************/

void ComponentTransform::set_rot(const glm::vec3 &rot)
{
    m_rot = glm::quat(rot);
}

/*******************************************************************************/

void ComponentTransform::set_matrix(const glm::mat4 &mat)
{
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(mat, m_scale, m_rot, m_pos, skew, perspective);
}

/*******************************************************************************/

void ComponentTransform::set_scale(const glm::vec3 &scale) { m_scale = scale; }

/*******************************************************************************/

void ComponentTransform::translate(const glm::vec3 &pos) { m_pos += pos; }

/*******************************************************************************/

void ComponentTransform::rotate(const glm::vec3 &rot)
{
    glm::vec3 c_rot = glm::eulerAngles(m_rot);

    c_rot += rot;

    m_rot = glm::quat(c_rot);
}

/*******************************************************************************/

void ComponentTransform::scale(const glm::vec3 &scale) { m_scale *= scale; }

/*******************************************************************************/

glm::vec3 ComponentTransform::get_pos() const { return m_pos; }

/*******************************************************************************/

glm::vec3 ComponentTransform::get_rot() const
{
    return glm::eulerAngles(m_rot);
}

/*******************************************************************************/

glm::quat ComponentTransform::get_rot_quat() const { return m_rot; }

/*******************************************************************************/

glm::vec3 ComponentTransform::get_scale() const { return m_scale; }

/*******************************************************************************/

glm::mat4 ComponentTransform::get_matrix() const { return build_matrix(); }

/*******************************************************************************/

void ComponentTransform::setup_render()
{
    if (m_update)
    {
        glm::mat4 mat = build_matrix();
        glm::mat3 mat_normal(glm::transpose(glm::inverse(mat)));
        glUniformMatrix4fv(10, 1, GL_FALSE, glm::value_ptr(mat));
        glUniformMatrix3fv(11, 1, GL_FALSE, glm::value_ptr(mat_normal));
    }
}

/*******************************************************************************/

void ComponentTransform::render_forward(bool override_shaders) const {}

/*******************************************************************************/

void ComponentTransform::tick() {}

/*******************************************************************************/

ComponentTransform::~ComponentTransform() {}

} // namespace Core
} // namespace FW