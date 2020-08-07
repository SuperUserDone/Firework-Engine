#include "input/InputMouse.hpp"

namespace FW
{
namespace Input
{

double InputMouse::get_mouse_x() { return m_x; }

double InputMouse::get_mouse_y() { return m_y; }

void InputMouse::set_fps_cursor(bool cursor)
{
    if (!m_window)
        return;

    if (cursor)
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    else
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void InputMouse::set_cursor_pos(double x, double y)
{
    m_x = x;
    m_y = y;
    glfwSetCursorPos(m_window, x, y);
}

void InputMouse::set_mouse_provider(const MouseSource &source)
{
    m_x = 0;
    m_y = 0;
    m_source = source;
}

bool InputMouse::is_mouse_button_down(MouseButton btn)
{
    // TODO
    return false;
}

void InputMouse::glfw_mouse_callback(GLFWwindow *window, double x, double y)
{
    m_x = x;
    m_y = y;
}

void InputMouse::imgui_mouse_callback(double x, double y)
{
    m_x = x;
    m_y = y;
}

void InputMouse::scroll_callback(GLFWwindow *window, double xoffset,
                                 double yoffset)
{ // TODO
}

} // namespace Input
} // namespace FW