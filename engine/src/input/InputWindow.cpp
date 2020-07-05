#include "input/InputWindow.hpp"

#include <glad/glad.h>

namespace FW
{
namespace Input
{

void InputWindow::init(int x, int y)
{
    sizex = x;
    sizey = y;
}

uint InputWindow::get_window_width() { return sizex; }

uint InputWindow::get_window_height() { return sizey; }

void InputWindow::set_resize_provider(WindowSource provider)
{
    m_provider = provider;
}

void InputWindow::imgui_resize_callback(uint width, uint height)
{
    if (m_provider != WINDOW_SOURCE_IMGUI)
        return;

    sizex = width;
    sizey = height;
}

void InputWindow::glfw_resize_callback(GLFWwindow *win, int width, int height)
{
    if (m_provider != WINDOW_SOURCE_GLFW)
        return;

    sizex = width;
    sizey = height;
}

} // namespace Input
} // namespace FW