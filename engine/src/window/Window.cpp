#include <functional>

#include "window/Window.hpp"

namespace FW
{
namespace Window
{

void Window::init_glfw() { glfwInit(); }

/*******************************************************************************/

void Window::make_window()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(  //
        m_settings.width,         //
        m_settings.height,        //
        m_settings.title.c_str(), //
        nullptr,                  //
        nullptr                   //
    );

    if (m_window == nullptr)
    {
        glfwTerminate();
        exit(-1);
    }
}

/*******************************************************************************/

void Window::init_opengl()
{
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        exit(-1);
    }

    glViewport(0, 0, m_settings.width, m_settings.height);
}

/*******************************************************************************/

Window::Window(const WindowSettings &settings) : m_settings(settings)
{
    init_glfw();
    make_window();
    init_opengl();
}

/*******************************************************************************/

void Window::poll_events() { glfwPollEvents(); }

/*******************************************************************************/

void Window::swap_buffers() { glfwSwapBuffers(m_window); }

/*******************************************************************************/

bool Window::check_close() { return glfwWindowShouldClose(m_window); }

/*******************************************************************************/

Window::~Window() { glfwTerminate(); }

} // namespace Window
} // namespace FW
