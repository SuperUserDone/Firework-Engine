#pragma once

#include <array>
#include <string>
#include <vector>

#include <glad/glad.h>

namespace FW
{
namespace Render
{

class CubeMap
{
private:
    uint m_texture;

    std::string m_path;

    int m_width;
    int m_height;
    int m_channels;
    int m_depth;

    std::vector<std::vector<uint8_t>> m_data;

public:
    CubeMap();
    CubeMap(const std::string &path);

    void set_load_params(const std::string &path);

    void async_safe_load();
    void sync_only_load();

    void bind(int slot);

    void unload();

    ~CubeMap();
};

} // namespace Render
} // namespace FW
