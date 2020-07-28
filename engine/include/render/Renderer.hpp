#pragma once

namespace FW
{
namespace Render
{

class Renderer
{
protected:
    bool m_alpha = false;

public:
    virtual void set_alpha(bool alpha) { m_alpha = true; }
    virtual bool get_alpha() { return m_alpha; }

    virtual void update() {}

    virtual void queue_render() = 0;
};

} // namespace Render
} // namespace FW