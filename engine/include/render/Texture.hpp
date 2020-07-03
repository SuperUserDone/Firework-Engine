#pragma once

#include <memory>
#include <string>

#include "io/binary/BinaryBuffer.hpp"
#include "render/TextureConfig.hpp"

namespace FW
{
namespace Render
{

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

class Texture
{
private:
    uint m_texture;

    std::string m_path;

    TextureConfig m_config;

    int m_width;
    int m_height;
    int m_channels;

    std::vector<uint8_t> m_data;

public:
    Texture();
    Texture(const std::string &path);
    Texture(const TextureConfig &config, const std::string &path);

    void set_load_params(const std::string &path);

    void async_safe_load();
    void sync_only_load();

    void bind(int slot);

    void unload();

    ~Texture();
};

} // namespace Render
} // namespace FW
