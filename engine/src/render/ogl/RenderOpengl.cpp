#include "render/ogl/RenderOpengl.hpp"
#include <loguru.hpp>

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

    glViewport(0, 0, 800, 600);

    // glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    // glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
#ifndef __NDEBG__
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
#endif

    //! TEMP

    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG_F(ERROR, "%s", infoLog);
        throw std::runtime_error("Failed to compile Vertex shader");
    }
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG_F(ERROR, "%s", infoLog);
        throw std::runtime_error("Failed to compile fragment shader");
    }
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOG_F(ERROR, "%s", infoLog);
        throw std::runtime_error("Failed to link shader");
    }

    LOG_F(INFO, "%s", "Shader compiled");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(shaderProgram);

    //! TEMP
}

uint RenderOpengl::create_texture(const TextureCreateParams &params)
{
    return 0;
}
void RenderOpengl::bind_texture(uint slot, uint texture) {}

void RenderOpengl::delete_texture(uint texture) {}

uint RenderOpengl::create_model(const ModelCreateParams &params)
{
    // Sanity checks
    {
        // Context
        if (m_asset_contexts.find(params.asset_context) ==
            m_asset_contexts.end())
            throw std::invalid_argument("Context invaild for model creation");

        // Mesh
        if (!params.mesh)
            throw std::invalid_argument(
                "Mesh cannot be null for model creation. "
                "This should be IMPOSSIBLE with the normal api. "
                "DO NOT USE RENDER SERVER API DIRECTLY!!! "
                "IT WILL BREAK IF YOU DO.");
    }

    _Model model;

    // Generating
    {
        glGenVertexArrays(1, &model.array_buffer);
        glGenBuffers(1, &model.data_buffer);
        glGenBuffers(1, &model.element_buffer);
    }

    // Filling
    {
        glBindBuffer(GL_ARRAY_BUFFER, model.array_buffer);
        glBufferData(GL_ARRAY_BUFFER,
                     params.mesh->get_data().size() * sizeof(Core::Vertex),
                     params.mesh->get_data().data(),
                     params.mesh->is_static() ? GL_STATIC_DRAW
                                              : GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.element_buffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                     params.mesh->get_index_data().size() * sizeof(uint),
                     params.mesh->get_index_data().data(),
                     params.mesh->is_static() ? GL_STATIC_DRAW
                                              : GL_DYNAMIC_DRAW);
    }

    // Setting Attribs
    {
        glBindVertexArray(model.array_buffer);
        glBindBuffer(GL_ARRAY_BUFFER, model.array_buffer);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Core::Vertex),
                              (void *)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Core::Vertex),
                              (void *)offsetof(Core::Vertex, normal));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Core::Vertex),
                              (void *)offsetof(Core::Vertex, uvs));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Core::Vertex),
                              (void *)offsetof(Core::Vertex, tangent));
    }

    // Meta Data
    {
        model.model_id = m_model_id_index++;
        model.index_size = params.mesh->get_index_data().size();
        model.context_id = params.asset_context;

        m_models[model.model_id] = model;

        Asset asset;

        asset.type = ASSET_TYPE_MODEL;
        asset.value = model.model_id;

        m_asset_contexts[model.context_id].m_assets.push_back(asset);
    }

    return model.model_id;
}

void RenderOpengl::draw_model(uint model)
{
    _Model model_temp = m_models[model];

    glBindVertexArray(model_temp.array_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model_temp.element_buffer);
    glDrawElements(GL_TRIANGLES, model_temp.index_size, GL_UNSIGNED_INT, 0);
}

void RenderOpengl::delete_model(uint model)
{
    _Model model_temp = m_models[model];

    glDeleteVertexArrays(1, &model_temp.array_buffer);
    glDeleteBuffers(1, &model_temp.element_buffer);
    glDeleteBuffers(1, &model_temp.data_buffer);
}

uint RenderOpengl::create_material(const MaterialCreateParams &params)
{
    return 0;
}

void RenderOpengl::set_model_properties(const ModelProperties &props)
{
    bind_material(props.material);

    glm::mat3 normal =
        glm::mat3(glm::transpose(glm::inverse(props.model_matrix)));

    glUniformMatrix4fv(10, 1, GL_FALSE, &props.model_matrix[0][0]);
    glUniformMatrix3fv(11, 1, GL_FALSE, &normal[0][0]);
}

void RenderOpengl::bind_material(uint material) {}

void RenderOpengl::delete_material(uint material) {}

uint RenderOpengl::new_asset_context(const AssetContextParams &params)
{
    AssetContext context;

    context.id = m_context_id_index++;
    m_asset_contexts[context.id] = context;

    return context.id;
}

void RenderOpengl::delete_asset_context(uint context)
{
    for (auto &&asset : m_asset_contexts[context].m_assets)
    {
        switch (asset.type)
        {
        case ASSET_TYPE_MODEL:
            delete_model(asset.value);
            break;
        case ASSET_TYPE_TEXTURE:
            delete_texture(asset.value);
            break;

        case ASSET_TYPE_MATERIAL:
            delete_material(asset.value);
            break;

        default:
            break;
        }
    }
}

void RenderOpengl::set_camera(const CameraParams &params) {}

void RenderOpengl::add_to_sorted_drawlist(const DrawCommand &command)
{
    std::lock_guard<std::mutex> lock(m_render_lock);
    m_sorted_draw.push_back(command);
}

void RenderOpengl::add_to_opaque_drawlist(const DrawCommand &command)
{
    std::lock_guard<std::mutex> lock(m_render_lock);
    m_opaque_draw.push_back(command);
}

void RenderOpengl::clear_drawlists()
{
    std::lock_guard<std::mutex> lock(m_render_lock);
    m_sorted_draw.clear();
    m_opaque_draw.clear();
}

void RenderOpengl::render()
{

    std::vector<DrawCommand> unsorted;
    std::vector<DrawCommand> sorted;

    // Copy commandlist
    {
        std::lock_guard<std::mutex> lock(m_render_lock);
        unsorted = m_opaque_draw;
        sorted = m_sorted_draw;
    }

    // Clear pass
    {
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    // Forward Pass
    {
        for (auto &&command : unsorted)
        {
            switch (command.type)
            {
            case DRAW_COMMAND_MODEL:
                // set_model_properties(command.data.model.props);
                draw_model(command.data.model.model);
                break;

            default:
                break;
            }
        }
    }

    // Transparency pass
    {}

    // Postprocess pass
    {}

    // Present pass
    {
    }
}

RenderOpengl::~RenderOpengl()
{
    for (auto &&context : m_asset_contexts)
    {
        delete_asset_context(context.first);
    }
}

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
