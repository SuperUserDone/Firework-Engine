#include "render/CubeMap.hpp"

#include <stb_image.h>

namespace FW
{
namespace Render
{

CubeMap::CubeMap() {}

/*******************************************************************************/

CubeMap::CubeMap(const std::string &path) : m_path(path) {}

/*******************************************************************************/

void CubeMap::set_load_params(const std::string &path) { m_path = path; }

/*******************************************************************************/

void CubeMap::async_safe_load()
{

    size_t pos_start = m_path.find("[");
    size_t pos_end = m_path.find("]");

    int start_num = 0;
    int end_num = 0;

    if (pos_start != std::string::npos && pos_end != std::string::npos)
    {
        end_num =
            atoi(m_path.substr(pos_start + 1, pos_end - pos_start).c_str());
    }
    for (size_t i = start_num; i <= end_num; i++)
    {
        std::string modded_path = m_path;
        if (end_num != 0)
            modded_path.replace(pos_start, pos_end + 1 - pos_start,
                                std::to_string(i));
        uint8_t *data =
            stbi_load(modded_path.c_str(), &m_width, &m_height, &m_channels, 0);

        m_data.push_back(
            std::vector<uint8_t>(data, data + m_width * m_height * m_channels));

        stbi_image_free(data);
    }
}

/*******************************************************************************/

void CubeMap::sync_only_load()
{
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

    for (size_t i = 0; i < m_data.size(); i++)
    {
        for (size_t j = 0; j < 6; j++)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + j, i, GL_RGB, m_width,
                         m_width, 0, GL_RGB, GL_UNSIGNED_BYTE,
                         &m_data[i][(m_width * m_width * m_channels) * j]);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    m_loaded = true;
}

/*******************************************************************************/

void CubeMap::bind(int slot)
{
    if (m_loaded)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
    }
}

/*******************************************************************************/

void CubeMap::unload() {}

/*******************************************************************************/

CubeMap::~CubeMap() {}

} // namespace Render
} // namespace FW