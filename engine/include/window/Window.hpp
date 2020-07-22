#pragma once

#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <loguru.hpp>
namespace FW
{
namespace Window
{

struct WindowSettings
{
    std::string title;

    int width = 800;
    int height = 600;

    enum : uint8_t
    {
        WINDOW_FULLSCREEN,
        WINDOW_BORDERLESS,
        WINDOW_WINDOWED
    } mode;

    bool vsync = false;
};

class Window
{
private:
    // Data
    WindowSettings m_settings;

    GLFWwindow *m_window = nullptr;

    // Methods
    void init_glfw();

public:
    Window(const WindowSettings &settings);

    void make_window();
    void poll_events();
    void swap_buffers();

    void make_current();

    bool check_close();

    ~Window();
};

} // namespace Window
} // namespace FW