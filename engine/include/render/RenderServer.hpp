#pragma once

#include <unordered_map>
#include <vector>

namespace FW
{
namespace Render
{

enum RendererBackend
{
    RENDER_BACKEND_DUMMY,
    RENDER_BACKEND_OPENGL43
};

class RenderServer
{
private:
public:
    RenderServer(RendererBackend backend = RENDER_BACKEND_OPENGL43);
    ~RenderServer();
};

} // namespace Render
} // namespace FW
