#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

#include "render/RendererMesh.hpp"

namespace FW
{
namespace Core
{

class ComponentTransform
{
private:
    glm::vec3 m_pos = glm::vec3(0.f);
    glm::vec3 m_scale = glm::vec3(1.f);
    glm::quat m_rot = glm::quat(glm::vec3(0.f, 0.f, 0.f));

public:
    ComponentTransform() = default;
    ComponentTransform(const glm::vec3 &pos);
    ComponentTransform(const glm::mat4 &transform);

    ComponentTransform(const glm::vec3 &pos,
                       const glm::vec3 &rot,
                       const glm::vec3 &scale);

    ComponentTransform(const glm::vec3 &pos,
                       const glm::quat &rot,
                       const glm::vec3 &scale);

    glm::vec3 get_pos() const { return m_pos; }
    glm::quat get_rotation() const { return m_rot; }
    glm::vec3 get_scale() const { return m_scale; }

    void set_transform(const glm::mat4 &transform)
    {
        glm::vec3 s;
        glm::vec4 p;

        glm::decompose(transform, m_scale, m_rot, m_pos, s, p);
    };

    void set_pos(const glm::vec3 &pos) { m_pos = pos; }
    void set_scale(const glm::vec3 &scale) { m_scale = scale; }
    void set_rot(const glm::vec3 &rot) { m_rot = glm::quat(rot); }
    void set_rot(const glm::quat &rot) { m_rot = rot; }

    void set_pos(double x, double y, double z) { m_pos = {x, y, z}; }
    void set_scale(double x, double y, double z) { m_scale = {x, y, z}; }
    void set_rot(double pitch, double yaw, double roll)
    {
        m_rot = glm::quat({pitch, yaw, roll});
    }
    void set_rot(double x, double y, double z, double w)
    {
        m_rot = glm::quat(x, y, z, w);
    }

    void translate(const glm::vec3 &vector) { m_pos += vector; }
    void scale(const glm::vec3 &scale) { m_scale *= scale; }
    void rotate(const glm::vec3 &rot) { m_rot = glm::rotate(m_rot, rot); }
    void rotate(const glm::quat &rot) { m_rot *= rot; }

    void translate(double x, double y, double z) { translate({x, y, z}); }
    void scale(double x, double y, double z) { scale({x, y, z}); }
    void rotate(double pitch, double yaw, double roll)
    {
        rotate({pitch, yaw, roll});
    }
    void rotate(double x, double y, double z, double w)
    {
        rotate(glm::quat(x, y, z, w));
    }

    void look_at(const glm::vec3 &target)
    {
        set_transform(glm::lookAt(m_pos, target, glm::vec3(0, 1, 0)));
    }

    operator glm::mat4() const;
};

struct ComponentRenderMesh
{
    Render::RendererMesh mesh;
};

struct ComponentMaterial
{
};

struct ComponentCamera
{
};

struct ComponentRelationship
{
};

struct ComponentTag
{
    std::string name;
};

} // namespace Core
} // namespace FW