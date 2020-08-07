#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

namespace FW
{
namespace Core
{

class Texture;
typedef std::shared_ptr<Texture> TexturePtr;

enum TextureScaleFilter
{
    TEXTURE_FILTER_NEAREST,
    TEXTURE_FILTER_LINEAR,
    TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR,
    TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST,
    TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR,
    TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST
};

enum WrapMode
{
    TEXTURE_WRAP_CLAMP,
    TEXTURE_WRAP_REPEAT,
    TEXTURE_WRAP_MIRRORED_REPEAT,
};

enum TextureType
{
    TEXTURE_TYPE_1D,
    TEXTURE_TYPE_2D,
    TEXTURE_TYPE_3D,
    TEXTURE_TYPE_CUBEMAP
};

struct TextureParams
{
    TextureScaleFilter min = TEXTURE_FILTER_LINEAR;
    TextureScaleFilter mag = TEXTURE_FILTER_LINEAR;

    TextureType type = TEXTURE_TYPE_2D;

    WrapMode wrap = TEXTURE_WRAP_REPEAT;

    bool gen_mipmaps = false;
    bool is_static = true;
};

class Texture
{
private:
    TextureParams m_params;
    std::string m_res_path;

    std::shared_ptr<std::vector<uint8_t>> m_data;

    uint m_id = 0;

public:
    Texture();
    Texture(const std::string &res_path, const TextureParams &params = {});

    // Transforms
    void resize(uint x, uint y, uint z = 0);

    // Loading
    void load(const std::string &res_path, const TextureParams &params = {});
    void reload();
    void full_reload();

    uint get_id();

    ~Texture();
};

} // namespace Core
} // namespace FW