#pragma once

#include <atomic>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace FW
{
namespace Input
{

enum WindowSource
{
    WINDOW_SOURCE_GLFW,
    WINDOW_SOURCE_IMGUI
};

class InputWindow
{
private:
    static inline std::atomic_int sizex;
    static inline std::atomic_int sizey;

    static inline WindowSource m_provider = WINDOW_SOURCE_GLFW;

public:
    static void init(int x, int y);

    static uint get_window_width();
    static uint get_window_height();

    static void set_resize_provider(WindowSource provider);

    static void resize_internal(uint x, uint y);

    static void imgui_resize_callback(uint width, uint height);
    static void glfw_resize_callback(GLFWwindow *win, int width, int height);
};

} // namespace Input
} // namespace FW
