#include "render/ogl/RenderOpengl.hpp"

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id,
                            GLenum severity, GLsizei length,
                            const char *message, const void *userParam);
namespace FW
{
namespace Render
{
namespace Backend
{

RenderOpengl::RenderOpengl()
{
    ZoneScopedN("Opengl init");
    LOG_F(INFO, "Loading OpenGL");

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_F(FATAL, "Failed to load OpenGL");
        std::terminate();
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

uint RenderOpengl::create_texture(const TextureCreateParams &params)
{
    return 0;
}
void RenderOpengl::bind_texture(uint slot, uint texture) {}

void RenderOpengl::delete_texture(uint texture) {}

uint RenderOpengl::create_model(const ModelCreateParams &params) { return 0; }

void RenderOpengl::bind_model(uint model) {}

void RenderOpengl::delete_model(uint model) {}

uint RenderOpengl::create_material(const MaterialCreateParams &params)
{
    return 0;
}

void RenderOpengl::bind_material(uint material) {}

void RenderOpengl::delete_material(uint material) {}

uint RenderOpengl::new_asset_context(const AssetContextParams &params)
{
    return 0;
}

void RenderOpengl::delete_asset_context(uint context) {}

void RenderOpengl::set_camera(const CameraParams &params) {}

void RenderOpengl::add_to_sorted_drawlist(const DrawCommand &command) {}

void RenderOpengl::add_to_opaque_drawlist(const DrawCommand &command) {}

void RenderOpengl::render() { glClear(GL_COLOR_BUFFER_BIT); }

RenderOpengl::~RenderOpengl() {}

} // namespace Backend
} // namespace Render
} // namespace FW

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id,
                            GLenum severity, GLsizei length,
                            const char *message, const void *userParam)
{
    // ignore non-significant error/warning codes
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204 || id == 1)
        return;

    int status = 0;

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
