#include "render/MeshRenderer.hpp"

namespace FW
{
namespace Render
{

MeshRenderer::MeshRenderer(const std::vector<Vertex> &data) : m_data(data) {}

/*******************************************************************************/

void MeshRenderer::update(const std::vector<Vertex> &data, int mode, int begin,
                          int end, bool re_alloc)
{
}

/*******************************************************************************/

void MeshRenderer::load_ogl()
{
    // !!!! SEPERATE
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
        "void main() {\n FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n }\n\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    // !!!! SEPERATE

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_data.size(), m_data.data(),
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);
    m_is_loaded = true;
}

/*******************************************************************************/

void MeshRenderer::update_ogl() {}

/*******************************************************************************/

void MeshRenderer::unload_ogl() {}

/*******************************************************************************/

void MeshRenderer::render_forward() const
{
    if (!m_is_loaded)
        return;
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

/*******************************************************************************/

MeshRenderer::~MeshRenderer() {}

} // namespace Render
} // namespace FW