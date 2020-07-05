#include <functional>
#include <iostream>

#include <Tracy.hpp>
#include <loguru.hpp>

#include "window/Window.hpp"

#include "input/InputKeyboard.hpp"
#include "input/InputWindow.hpp"

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id,
                            GLenum severity, GLsizei length,
                            const char *message, const void *userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204 || id == 1)
        return;

    int status;

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        status = -2;
        break;
    case GL_DEBUG_SEVERITY_MEDIUM:
        status = -1;
        break;
    case GL_DEBUG_SEVERITY_LOW:
        status = 0;
        break;
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        status = 0;
        break;
    }

    VLOG_SCOPE_F(status, "OpenGL: %d %s", id, message);

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        VLOG_F(status, "Source: API");
        break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        VLOG_F(status, "Source: Window System");
        break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        VLOG_F(status, "Source: Shader Compiler");
        break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
        VLOG_F(status, "Source: Third Party");
        break;
    case GL_DEBUG_SOURCE_APPLICATION:
        VLOG_F(status, "Source: Application");
        break;
    case GL_DEBUG_SOURCE_OTHER:
        VLOG_F(status, "Source: Other");
        break;
    }

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        VLOG_F(status, "Type: Error");
        break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        VLOG_F(status, "Type: Deprecated Behaviour");
        break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        VLOG_F(status, "Type: Undefined Behaviour");
        break;
    case GL_DEBUG_TYPE_PORTABILITY:
        VLOG_F(status, "Type: Portability");
        break;
    case GL_DEBUG_TYPE_PERFORMANCE:
        VLOG_F(status, "Type: Performance");
        break;
    case GL_DEBUG_TYPE_MARKER:
        VLOG_F(status, "Type: Marker");
        break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
        VLOG_F(status, "Type: Push Group");
        break;
    case GL_DEBUG_TYPE_POP_GROUP:
        VLOG_F(status, "Type: Pop Group");
        break;
    case GL_DEBUG_TYPE_OTHER:
        VLOG_F(status, "Type: Other");
        break;
    }
}

namespace FW
{
namespace Window
{

void Window::init_glfw()
{
    ZoneScopedN("GLFW init");
    LOG_F(INFO, "Init GLFW");
    glfwInit();
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

    glfwSetWindowSizeCallback(m_window,
                              &Input::InputWindow::glfw_resize_callback);
    glfwSetKeyCallback(m_window, &Input::InputKeyboard::key_callback);
    glfwSetCharCallback(m_window, &Input::InputKeyboard::character_callback);
}

/*******************************************************************************/

void Window::init_opengl()
{
    ZoneScopedN("Opengl init");
    LOG_F(INFO, "Loading OpenGL");
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_F(FATAL, "Failed to load OpenGL");
        glfwTerminate();
        exit(-1);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
}

void Window::init_imgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init("#version 430 core");
}

/*******************************************************************************/

Window::Window(const WindowSettings &settings) : m_settings(settings)
{
    loguru::g_stderr_verbosity = 1;
    ZoneScopedN("Window init");
    init_glfw();
    make_window();
    init_opengl();
    init_imgui();
}

/*******************************************************************************/

void Window::poll_events()
{
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

bool Window::check_close() { return glfwWindowShouldClose(m_window); }

/*******************************************************************************/

Window::~Window()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

} // namespace Window
} // namespace FW
