#pragma once

#include <atomic>
#include <string>

#include "render/Shader.hpp"

namespace FW
{
namespace Render
{

class Material
{
private:
    std::string m_path;
    std::atomic_bool m_loaded;

    Shader m_shader;

public:
    Material(const std::string &mat_path);

    void load_assets();
    void load_ogl();

    void activate() const;

    ~Material();
};

} // namespace Render
} // namespace FW