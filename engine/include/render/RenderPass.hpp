#pragma once

#include <memory>

#include "render/Framebuffer.hpp"

namespace FW
{
namespace Render
{

enum RenderPass
{
    RENDERPASS_RESET,
    RENDERPASS_FORWARD,
    RENDERPASS_POST_PROCESS,
    RENDERPASS_UI,
    RENDERPASS_DONE
};

} // namespace Render
} // namespace FW
