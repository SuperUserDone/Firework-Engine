#include <functional>
#include <iostream>

#include <Tracy.hpp>
#include <loguru.hpp>

#include "window/Window.hpp"

#include "input/InputKeyboard.hpp"
#include "input/InputMouse.hpp"
#include "input/InputWindow.hpp"

namespace FW
{
namespace Window
{

void Window::init_glfw()
{
    ZoneScopedN("GLFW init");
    LOG_F(INFO, "Init GLFW");
    if (!glfwInit())
        std::abort();
}

/*******************************************************************************/

void Window::make_window()
{
    ZoneScopedN("Window Creation");
    LOG_F(INFO, "Creating Window %s.", m_settings.title.c_str());
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
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
        LOG_F(FATAL, "Failed to open window!");
        glfwTerminate();
        exit(-1);
    }

    Input::InputWindow::init(m_settings.width, m_settings.height);
    Input::InputWindow::set_resize_provider(Input::WINDOW_SOURCE_GLFW);

    Input::InputKeyboard::set_window(m_window);
    Input::InputMouse::set_window(m_window);

    glfwSetWindowSizeCallback(m_window,
                              &Input::InputWindow::glfw_resize_callback);
    glfwSetCharCallback(m_window, &Input::InputKeyboard::character_callback);
    glfwSetCursorPosCallback(m_window, &Input::InputMouse::glfw_mouse_callback);
}

/*******************************************************************************/

void Window::make_current() { glfwMakeContextCurrent(m_window); }

/*******************************************************************************/

Window::Window(const WindowSettings &settings) : m_settings(settings)
{
    loguru::g_stderr_verbosity = 1;
    ZoneScopedN("Window init");
    init_glfw();
}

/*******************************************************************************/

void Window::poll_events()
{
    if (!m_window)
        return;
    // ZoneScopedN("Event Polling");
    glfwPollEvents();
}

/*******************************************************************************/

void Window::swap_buffers()
{
    ZoneScopedN("Buffer Swap");
    glfwSwapBuffers(m_window);
}

/*******************************************************************************/

bool Window::check_close()
{
    if (!m_window)
        return false;
    return glfwWindowShouldClose(m_window);
}

/*******************************************************************************/

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

} // namespace Window
} // namespace FW
