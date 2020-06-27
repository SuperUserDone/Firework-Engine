#pragma once

#include <atomic>
#include <memory>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace FW
{
namespace Window
{

class RuntimeProperties
{
private:
    static inline std::atomic_int sizex;
    static inline std::atomic_int sizey;

public:
    static void resize_callback(GLFWwindow *win, int width, int height)
    {
        sizex = width;
        sizey = height;
        glViewport(0, 0, width, height);
    }

    static void get_window_size(int &x, int &y)
    {
        x = sizex;
        y = sizey;
    }
};

} // namespace Window
} // namespace FW