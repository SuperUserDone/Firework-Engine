#include "core/manager/AssetManager.hpp"
#include "core/misc/Texture.hpp"

#include "render/RenderServer.hpp"

namespace FW
{
namespace Core
{

Texture::Texture() {}

Texture::Texture(const std::string &res_path, const TextureParams &params)
{
    load(res_path, params);
}

void Texture::load(const std::string &res_path, const TextureParams &params)
{
    m_res_path = res_path;
    m_params = params;

    full_reload();
}

void Texture::reload()
{
    Render::Backend::TextureCreateParams m_texture_params;
    m_texture_params.asset_context = 0;

    // TODO
    // m_texture_params.data = m_data->data();
    uint8_t data[] = {128, 128, 128};
    m_texture_params.data = data;
    m_texture_params.channels = 3;
    m_texture_params.sizex = 1;
    m_texture_params.sizey = 1;
    m_texture_params.scale_mag = m_params.mag;
    m_texture_params.scale_min = m_params.min;
    m_texture_params.type = m_params.type;
    m_texture_params.wrap = m_params.wrap;

    Render::RenderServer &m_server = Render::RenderServer::get_instance();

    if (m_id.has_value())
        m_server.delete_texture(m_id.value());

    m_id = m_server.create_texture(m_texture_params).get();
}

void Texture::full_reload()
{
    m_data = AssetManager::get_instance().load_data(m_res_path).get();

    reload();
}

uint Texture::get_id() { return m_id.value(); }

Texture::~Texture()
{
    Render::RenderServer &m_server = Render::RenderServer::get_instance();
    if (m_id)
        m_server.delete_texture(m_id.value());
}

} // namespace  Core
} // namespace FW