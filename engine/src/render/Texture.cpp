#define STB_IMAGE_IMPLEMENTATION
#include "render/Texture.hpp"
#include "stb_image.h"

#include <Tracy.hpp>
#include <glad/glad.h>
#include <loguru.hpp>

namespace FW
{
namespace Render
{

Texture::Texture() {}

/*******************************************************************************/

Texture::Texture(const std::string &path) : m_path(path) {}

/*******************************************************************************/

Texture::Texture(const TextureConfig &config, const std::string &path) {}

/*******************************************************************************/

void Texture::set_load_params(const std::string &path) {}

/*******************************************************************************/

void Texture::async_safe_load()
{
    ZoneScopedN("Load Texture");
    LOG_F(INFO, "Loading Texture: %s", m_path.c_str());
    uint8_t *data =
        stbi_load(m_path.c_str(), &m_width, &m_height, &m_channels, 0);

    if (!data)
    {
        LOG_F(ERROR, "Failed to load texture %s!", m_path.c_str());
    }

    m_data = std::vector<uint8_t>(data, data + m_width * m_height * m_channels);
    stbi_image_free(data);
}

/*******************************************************************************/

void Texture::sync_only_load()
{
    ZoneScopedN("Load Texture into Vram");
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_config.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_config.wrap_t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_config.filter_min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_config.filter_mag);

    switch (m_channels)
    {
    case 1:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_width, m_height, 0, GL_RED,
                     GL_UNSIGNED_BYTE, &m_data[0]);
        break;
    case 2:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, m_width, m_height, 0, GL_RG,
                     GL_UNSIGNED_BYTE, &m_data[0]);
        break;
    case 3:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB,
                     GL_UNSIGNED_BYTE, &m_data[0]);
        break;
    case 4:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, &m_data[0]);
        break;
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    m_loaded = true;
}

/*******************************************************************************/

void Texture::bind(int slot)
{
    if (m_loaded)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }
}

/*******************************************************************************/

void Texture::unload() {}

/*******************************************************************************/

Texture::~Texture() {}

} // namespace Render
} // namespace FW