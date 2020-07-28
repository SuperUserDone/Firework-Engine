#pragma once

#include <string>

namespace FW
{
namespace Core
{

enum TextureScaleFilter
{
    TEXTURE_FILTER_NEAREST,
    TEXTURE_FILTER_LINEAR,
    TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR,
    TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST,
    TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR,
    TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST
};

struct TextureParams
{
    TextureScaleFilter min = TEXTURE_FILTER_LINEAR;
    TextureScaleFilter mag = TEXTURE_FILTER_LINEAR;

    bool gen_mipmaps = false;
};

class Texture
{
private:
public:
    Texture();
    Texture(const std::string &res_path, const TextureParams &parms = {});

    ~Texture();
};

} // namespace Core
} // namespace FW