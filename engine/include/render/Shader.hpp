#pragma once

#include <string>

namespace FW
{
namespace Render
{
class Shader
{
private:
    std::string m_frag;
    std::string m_vert;

    uint m_program;

public:
    Shader();
    Shader(const std::string &frag, const std::string &vert);

    void set_frag(const std::string &frag);
    void set_vert(const std::string &vert);

    void load_ogl();

    void activate() const;

    ~Shader();
};

} // namespace Render
} // namespace FW