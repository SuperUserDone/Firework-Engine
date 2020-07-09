#include "core/ActionQueue.hpp"
#include "core/Scene.hpp"

namespace FW
{
namespace Core
{

void Scene::update_lamps() {}

/*******************************************************************************/

Scene::Scene()
{
    m_postprocess_loaded = false;
    ActionQueue::get_instance().add_top_action(std::make_shared<Action>( //
        []() {},                                                         //
        [this]() { this->setup_postprocess(); }));
}

/*******************************************************************************/

void Scene::add_ui_element(const std::function<void()> &func)
{
    m_ui_functions.push_back(func);
}

/*******************************************************************************/

void Scene::add_object(std::shared_ptr<ObjectBasic> obj)
{
    m_objects.push_back(obj);
}

/*******************************************************************************/

void Scene::add_light(std::shared_ptr<ObjectLight> obj) {}

/*******************************************************************************/

void Scene::add_camera(std::shared_ptr<ObjectCamera> obj)
{
    m_cameras.push_back(obj);
}

/*******************************************************************************/

void Scene::render_forward(uint framebuffer, bool override_shaders)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    if (framebuffer != 0)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    if (!m_cameras.empty())
        m_cameras.front()->setup_render();

    bool lamps_update = false;

    for (auto &&lamp : m_lights)
    {
        // TODO Logic for checking updates
    }

    if (lamps_update)
        update_lamps();

    std::for_each(std::begin(m_objects), std::end(m_objects),
                  [override_shaders](std::shared_ptr<ObjectBasic> obj) {
                      obj->setup_render();
                      obj->render_forward(override_shaders);
                  });
}

/*******************************************************************************/

void Scene::render_postprocess(uint framebuffer)
{
    if (m_postprocess_loaded)
    {
        m_postprocess_shader.activate();
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        if (framebuffer != 0)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        glDisable(GL_DEPTH_TEST);
        glBindVertexArray(m_quad_vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glEnable(GL_DEPTH_TEST);
    }
}

/*******************************************************************************/

void Scene::render_ui(uint framebuffer) {}

/*******************************************************************************/

void Scene::setup_postprocess()
{
    float quadVertices[] = {-1.0f, 1.0f,  0.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
                            1.0f,  -1.0f, 1.0f, 0.0f, -1.0f, 1.0f,  0.0f, 1.0f,
                            1.0f,  -1.0f, 1.0f, 0.0f, 1.0f,  1.0f,  1.0f, 1.0f};

    glGenVertexArrays(1, &m_quad_vao);
    glGenBuffers(1, &m_quad_buffer);
    glBindVertexArray(m_quad_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_quad_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices,
                 GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)(2 * sizeof(float)));

    m_postprocess_shader.set_vert(
        "assets/materials/shaders/screen.vertex.glsl");
    m_postprocess_shader.set_frag(
        "assets/materials/shaders/screen.fragment.glsl");
    m_postprocess_shader.load_ogl();

    m_postprocess_loaded = true;
}

/*******************************************************************************/

Scene::~Scene()
{
    glDeleteBuffers(1, &m_quad_vao);
    glDeleteVertexArrays(1, &m_quad_vao);
}

} // namespace Core
} // namespace FW