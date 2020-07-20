#pragma once

#include "render/RendererBase.hpp"
#include <glm/glm.hpp>

namespace FW
{
namespace Render
{

class QuadRenderer : public RendererBase
{
private:
public:
    QuadRenderer(glm::mat4 transform);

    // Loading
    virtual void load_ogl() override;
    virtual void update_ogl() override;
    virtual void unload_ogl() override;

    // Rendering
    virtual void render_forward() const override;

    ~QuadRenderer();
};

} // namespace Render
} // namespace FW
