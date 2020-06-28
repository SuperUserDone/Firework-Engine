#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

#include "core/ActionQueue.hpp"
#include "core/components/Component.hpp"
#include "render/Types.hpp"

namespace FW
{
namespace Core
{

class ComponentTransform : public Component
{
protected:
    glm::mat4 build_matrix() const;

    glm::vec3 m_pos;
    glm::quat m_rot;
    glm::vec3 m_scale;

    bool m_update = true;

public:
    ComponentTransform();

    // Loading
    virtual void load_assets();
    virtual void load_ogl();
    virtual void update_data();

    // Checks
    virtual ComponentType get_type() { return COMPONENT_TRANSFORM; }

    // Internal
    virtual void set_external_updates(bool state) { m_update = !state; }

    // Movement
    virtual void set_pos(const glm::vec3 &pos);
    virtual void set_rot(const glm::quat &rot);
    virtual void set_rot(const glm::vec3 &rot);
    virtual void set_scale(const glm::vec3 &scale);
    virtual void set_matrix(const glm::mat4 &mat);

    virtual void translate(const glm::vec3 &pos);
    virtual void rotate(const glm::vec3 &rot);
    virtual void scale(const glm::vec3 &scale);

    // Gets
    virtual glm::vec3 get_pos() const;
    virtual glm::vec3 get_rot() const;
    virtual glm::quat get_rot_quat() const;
    virtual glm::vec3 get_scale() const;
    virtual glm::mat4 get_matrix() const;

    // Rendering
    virtual void setup_render();
    virtual void render_forward() const;

    // Updating
    virtual void tick();

    ~ComponentTransform();
};

} // namespace Core
} // namespace FW