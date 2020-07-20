#pragma once

#include <memory>

namespace FW
{
namespace Render
{

class RendererBase;

typedef std::shared_ptr<RendererBase> RendererBasePtr;

class RendererBase
{
private:
public:
    // Loading
    virtual void load_ogl() = 0;
    virtual void update_ogl() = 0;
    virtual void unload_ogl() = 0;

    // Rendering
    virtual void render_forward() const = 0;
};
} // namespace Render

} // namespace FW
