#pragma once

#include <atomic>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace FW
{
namespace Input
{

enum MouseSource
{
    MOUSE_SOURCE_GLFW,
    MOUSE_SOURCE_IMGUI
};

enum MouseButton
{
    MOUSE_BUTTON_UNKOWN = -1,
    MOUSE_BUTTON_LEFT = 0,
    MOUSE_BUTTON_RIGHT = 1,
    MOUSE_BUTTON_MIDDLE = 2,
    MOUSE_BUTTON_EXTRA_1 = 3,
    MOUSE_BUTTON_EXTRA_2 = 4,
    MOUSE_BUTTON_EXTRA_3 = 5,
    MOUSE_BUTTON_EXTRA_4 = 6,
    MOUSE_BUTTON_EXTRA_5 = 7
};

class InputMouse
{
private:
    static inline MouseSource m_source;

    static inline double m_x = 0;
    static inline double m_y = 0;

    static inline GLFWwindow *m_window = nullptr;

public:
    static double get_mouse_x();
    static double get_mouse_y();

    static void set_fps_cursor(bool cursor);

    static void set_cursor_pos(double x, double y);

    static void set_mouse_provider(const MouseSource &source);

    static void set_window(GLFWwindow *window) { m_window = window; }

    static bool is_mouse_button_down(MouseButton btn);

    static void glfw_mouse_callback(GLFWwindow *window, double x, double y);

    static void imgui_mouse_callback(double x, double y);

    static void
    scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
};

} // namespace Input
} // namespace FW