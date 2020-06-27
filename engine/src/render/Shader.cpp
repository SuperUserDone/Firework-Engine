#include <fstream>
#include <iostream>

#include <glad/glad.h>

#include "render/Shader.hpp"

namespace FW
{
namespace Render
{

Shader::Shader() {}

/*******************************************************************************/

Shader::Shader(const std::string &frag, const std::string &vert)
    : m_frag(frag), m_vert(vert)
{
}

/*******************************************************************************/

void Shader::set_vert(const std::string &vert) { m_vert = vert; }

/*******************************************************************************/

void Shader::set_frag(const std::string &frag) { m_frag = frag; }

/*******************************************************************************/

void Shader::load_ogl()
{
    std::fstream vert(m_vert);
    std::fstream frag(m_frag);

    std::string frag_source((std::istreambuf_iterator<char>(frag)),
                            std::istreambuf_iterator<char>());
    std::string vert_source((std::istreambuf_iterator<char>(vert)),
                            std::istreambuf_iterator<char>());

    vert.close();
    frag.close();

    int success;
    uint vert_shader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertcstr = vert_source.c_str();
    glShaderSource(vert_shader, 1, &vertcstr, NULL);
    glCompileShader(vert_shader);

    glGetShaderiv(vert_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vert_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    uint frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragcstr = frag_source.c_str();
    glShaderSource(frag_shader, 1, &fragcstr, NULL);
    glCompileShader(frag_shader);

    glGetShaderiv(frag_shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(frag_shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }

    m_program = glCreateProgram();

    glAttachShader(m_program, vert_shader);
    glAttachShader(m_program, frag_shader);
    glLinkProgram(m_program);

    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glUseProgram(m_program);

    glDeleteShader(frag_shader);
    glDeleteShader(vert_shader);
}

/*******************************************************************************/

void Shader::activate() const { glUseProgram(m_program); }

/*******************************************************************************/

Shader::~Shader() { glDeleteProgram(m_program); }

} // namespace Render
} // namespace FW