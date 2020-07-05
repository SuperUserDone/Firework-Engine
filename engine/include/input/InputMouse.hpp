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
    static MouseSource source;

public:
    static uint get_mouse_x();
    static uint get_mouse_y();

    static void set_mouse_provider(const MouseSource &source);

    static bool is_mouse_button_down(MouseButton btn);

    static void cursor_position_callback(GLFWwindow *window, double xpos,
                                         double ypos);

    static void mouse_button_callback(GLFWwindow *window, int button,
                                      int action, int mods);

    static void scroll_callback(GLFWwindow *window, double xoffset,
                                double yoffset);
};

} // namespace Input
} // namespace FW