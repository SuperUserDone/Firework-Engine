#pragma once

#include <memory>
#include <sys/types.h>

#include <glad/glad.h>

namespace FW
{
namespace Render
{

class Framebuffer;

typedef std::shared_ptr<Framebuffer> FramebufferPtr;

class Framebuffer
{
private:
    uint m_framebuffer;
    uint m_texture;
    uint m_renderbuffer;

    uint m_multisample_buffer;
    uint m_multisample_texture;
    uint m_multisample_renderbuffer;

    uint m_width;
    uint m_height;

    bool msaa_renderstorage = false;
    bool base_renderstorage = false;

    bool m_multisampled = false;

    void gen_fbo(uint width, uint height, bool render_storage);
    void gen_msaa_fbo(uint width, uint height, bool render_storage,
                      uint multisample_count);

    bool custom = false;

public:
    Framebuffer(uint index) { m_framebuffer = index; }
    Framebuffer(uint width, uint height, bool render_storage);
    Framebuffer(uint width, uint height, bool render_storage,
                uint multisample_count);

    void resize(int width, int height);
    void bind_texture(uint slot);

    uint get_handle();

    uint get_texture();

    ~Framebuffer();
};

} // namespace Render
} // namespace FW