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

/**
 * \brief A window class used to abstract the core window funtionality using
 * GLFW
 *
 */
class Window
{
private:
    WindowSettings m_settings;

    GLFWwindow *m_window = nullptr;

    /**
     * \brief Init GLFW
     *
     */
    void init_glfw();

public:
    /**
     * \brief Constructor
     *
     * \param settings The window settings
     */
    Window(const WindowSettings &settings);

    /**
     * \brief Make the actual window (CALLED INTERNALY)
     *
     */
    void make_window();

    /**
     * \brief Poll events (CALLED INTERNALY)
     *
     */
    void poll_events();

    /**
     * \brief Swap Buffers (CALLED INTERNALY)
     *
     */
    void swap_buffers();

    /**
     * \brief Make Context (CALLED INTERNALY)
     *
     */
    void make_current();

    /**
     * \brief Check if the window should close
     *
     * \return true yes
     * \return false no
     */
    bool check_close();

    /**
     * \brief Destructor
     *
     */
    ~Window();
};

} // namespace Window
} // namespace FW