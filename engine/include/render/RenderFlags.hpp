#pragma once

namespace FW
{
namespace Render
{

enum RenderFlags
{
    RENDER_FLAG_MATERIAL = 0b1,
    RENDER_FLAG_CAMERA = 0b10,
    RENDER_FLAG_DEFAULT = 0b11
};

} // namespace Render
} // namespace FW
