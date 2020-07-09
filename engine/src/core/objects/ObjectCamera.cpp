#include <glad/glad.h>

#include "core/ActionQueue.hpp"
#include "core/components/ComponentTransform.hpp"
#include "core/objects/ObjectCamera.hpp"
#include "input/InputWindow.hpp"

namespace FW
{
namespace Core
{

void ObjectCamera::load_assets() {}

/*******************************************************************************/

void ObjectCamera::load_ogl()
{
    int x, y;
    x = Input::InputWindow::get_window_width();
    y = Input::InputWindow::get_window_height();
    last_x = x;
    last_y = y;

    m_projection =
        glm::perspective(glm::radians(90.f), (float)x / (float)y, 0.1f, 100.f);

    m_transform->set_matrix(
        glm::inverse(glm::lookAt(glm::vec3(1.0f, 1.0f, 0.0f), //
                                 glm::vec3(0.0f, 0.0f, 0.0f), //
                                 glm::vec3(0.0f, 0.0f, 1.0f))));

    glGenBuffers(1, &m_camera_buffer);

    glBindBuffer(GL_UNIFORM_BUFFER, m_camera_buffer);

    glBufferData(GL_UNIFORM_BUFFER,                         //
                 2 * sizeof(glm::mat4) + sizeof(glm::vec3), //
                 nullptr,                                   //
                 GL_STREAM_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // Set buffer pos
    glBindBufferRange(GL_UNIFORM_BUFFER, //
                      0,                 //
                      m_camera_buffer,   //
                      0, 2 * sizeof(glm::mat4) + sizeof(glm::vec3));

    glBindBuffer(GL_UNIFORM_BUFFER, m_camera_buffer);

    // Fill buffer
    glBufferSubData(GL_UNIFORM_BUFFER, //
                    0,                 //
                    sizeof(glm::mat4), //
                    glm::value_ptr(m_projection));

    glBufferSubData(GL_UNIFORM_BUFFER, //
                    sizeof(glm::mat4), //
                    sizeof(glm::mat4), //
                    glm::value_ptr(glm::inverse(m_transform->get_matrix())));

    glBufferSubData(GL_UNIFORM_BUFFER,     //
                    2 * sizeof(glm::mat4), //
                    sizeof(glm::vec3),     //
                    glm::value_ptr(m_transform->get_pos()));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    m_ready = true;
}

/*******************************************************************************/

void ObjectCamera::unload() {}

/*******************************************************************************/

ObjectCamera::ObjectCamera()
{
    m_ready = false;
    ActionQueue::get_instance().add_top_action(
        Action::new_action(std::bind(&ObjectCamera::load_assets, this),
                           std::bind(&ObjectCamera::load_ogl, this)));

    m_transform = std::make_shared<ComponentTransform>();
    m_transform->set_external_updates(true);
    m_components.push_back(m_transform);
}

/*******************************************************************************/

void ObjectCamera::look_at(const glm::vec3 &target)
{
    m_transform->set_matrix(
        glm::inverse(glm::lookAt(m_transform->get_pos(), //
                                 target,                 //
                                 glm::vec3(0.0f, 0.0f, 1.0f))));
}

/*******************************************************************************/

void ObjectCamera::add_component(std::shared_ptr<Component> comp) {}

/*******************************************************************************/

void ObjectCamera::setup_render()
{
    int x, y;
    x = Input::InputWindow::get_window_width();
    y = Input::InputWindow::get_window_height();

    m_projection =
        glm::perspective(glm::radians(90.f), (float)x / (float)y, 0.1f, 100.f);

    last_x = x;
    last_y = y;

    if (!m_ready)
        return;
    glBindBuffer(GL_UNIFORM_BUFFER, m_camera_buffer);

    // Fill buffer
    glBufferSubData(GL_UNIFORM_BUFFER, //
                    0,                 //
                    sizeof(glm::mat4), //
                    glm::value_ptr(m_projection));

    glBufferSubData(GL_UNIFORM_BUFFER, //
                    sizeof(glm::mat4), //
                    sizeof(glm::mat4), //
                    glm::value_ptr(glm::inverse(m_transform->get_matrix())));

    glBufferSubData(GL_UNIFORM_BUFFER,     //
                    2 * sizeof(glm::mat4), //
                    sizeof(glm::vec3),     //
                    glm::value_ptr(m_transform->get_pos()));

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

/*******************************************************************************/

void ObjectCamera::render_forward(bool override_shaders) const {}

/*******************************************************************************/

void ObjectCamera::tick() {}

/*******************************************************************************/

ObjectCamera::~ObjectCamera() {}

} // namespace Core
} // namespace FW