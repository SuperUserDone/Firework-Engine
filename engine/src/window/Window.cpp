#include <functional>
#include <iostream>

#include <Tracy.hpp>

#include "window/RuntimeProperties.hpp"
#include "window/Window.hpp"

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id,
                            GLenum severity, GLsizei length,
                            const char *message, const void *userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " << message << std::endl;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        std::cout << "Source: API";
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        std::cout << "Source: Window System";
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        std::cout << "Source: Shader Compiler";
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        std::cout << "Source: Third Party";
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        std::cout << "Source: Application";
        break;
    case GL_DEBUG_SOURCE_OTHER:
        std::cout << "Source: Other";
        break;
    }
    std::cout << std::endl;

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        std::cout << "Type: Error";
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        std::cout << "Type: Deprecated Behaviour";
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        std::cout << "Type: Undefined Behaviour";
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        std::cout << "Type: Portability";
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        std::cout << "Type: Performance";
        break;
    case GL_DEBUG_TYPE_MARKER:
        std::cout << "Type: Marker";
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        std::cout << "Type: Push Group";
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        std::cout << "Type: Pop Group";
        break;
    case GL_DEBUG_TYPE_OTHER:
        std::cout << "Type: Other";
        break;
    }
    std::cout << std::endl;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "Severity: high";
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        std::cout << "Severity: medium";
        break;
    case GL_DEBUG_SEVERITY_LOW:
        std::cout << "Severity: low";
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        std::cout << "Severity: notification";
        break;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}

namespace FW
{
namespace Window
{

void Window::init_glfw()
{
    ZoneScopedN("GLFW init");
    glfwInit();
}

/*******************************************************************************/

void Window::make_window()
{
    ZoneScopedN("Window Creation");
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
        glfwTerminate();
        exit(-1);
    }

    glfwSetWindowSizeCallback(m_window, &RuntimeProperties::resize_callback);
}

/*******************************************************************************/

void Window::init_opengl()
{
    ZoneScopedN("Opengl init");
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);

    RuntimeProperties::resize_callback(m_window, m_settings.width,
                                       m_settings.height);
}

/*******************************************************************************/

Window::Window(const WindowSettings &settings) : m_settings(settings)
{
    ZoneScopedN("Window init");
    init_glfw();
    make_window();
    init_opengl();
}

/*******************************************************************************/

void Window::poll_events()
{
    ZoneScopedN("Event Polling");
    RuntimeProperties::get_window_size(m_settings.width, m_settings.height);
    glfwPollEvents();
}

/*******************************************************************************/

void Window::swap_buffers()
{
    ZoneScopedN("Buffer Swap");
    glfwSwapBuffers(m_window);
}

/*******************************************************************************/

bool Window::check_close() { return glfwWindowShouldClose(m_window); }

/*******************************************************************************/

Window::~Window() { glfwTerminate(); }

} // namespace Window
} // namespace FW
