#include <glad/glad.h>

#include "core/ActionQueue.hpp"
#include "core/objects/ObjectCamera.hpp"

namespace FW
{
namespace Core
{

void ObjectCamera::load_assets() {}

/*******************************************************************************/

void ObjectCamera::load_ogl()
{
    m_projection =
        glm::perspective(glm::radians(90.f), 800.f / 600.f, 0.1f, 100.f);
    m_view = glm::lookAt(glm::vec3(0.0f, -2.0f, 0.0f), //
                         glm::vec3(0.0f, 0.0f, 0.0f), //
                         glm::vec3(0.0f, 0.0f, 1.0f));

    glGenBuffers(1, &m_camera_buffer);

    glBindBuffer(GL_UNIFORM_BUFFER, m_camera_buffer);

    glBufferData(GL_UNIFORM_BUFFER,     //
                 2 * sizeof(glm::mat4), //
                 nullptr,               //
                 GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Set buffer pos
    glBindBufferRange(GL_UNIFORM_BUFFER, //
                      0,                 //
                      m_camera_buffer,   //
                      0, 2 * sizeof(glm::mat4));

    glBindBuffer(GL_UNIFORM_BUFFER, m_camera_buffer);

    // Fill buffer
    glBufferSubData(GL_UNIFORM_BUFFER, //
                    0,                 //
                    sizeof(glm::mat4), //
                    glm::value_ptr(m_projection));

    glBufferSubData(GL_UNIFORM_BUFFER, //
                    sizeof(glm::mat4), //
                    sizeof(glm::mat4), //
                    glm::value_ptr(m_view));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

/*******************************************************************************/

void ObjectCamera::unload() {}

/*******************************************************************************/

ObjectCamera::ObjectCamera()
{
    ActionQueue::get_instance().add_top_action(
        Action::new_action(std::bind(&ObjectCamera::load_assets, this),
                           std::bind(&ObjectCamera::load_ogl, this)));
}

/*******************************************************************************/

void ObjectCamera::add_component(std::shared_ptr<Component> comp) {}

/*******************************************************************************/

void ObjectCamera::setup_render() {}

/*******************************************************************************/

void ObjectCamera::render_forward() const {}

/*******************************************************************************/

void ObjectCamera::tick() {}

/*******************************************************************************/

ObjectCamera::~ObjectCamera() {}

} // namespace Core
} // namespace FW