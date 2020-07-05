#include "render/Framebuffer.hpp"
#include "input/InputWindow.hpp"

namespace FW
{
namespace Render
{

void Framebuffer::gen_fbo(uint width, uint height, bool render_storage)
{
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           m_texture, 0);

    if (render_storage)
    {
        glGenRenderbuffers(1, &m_renderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width,
                              height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                  GL_RENDERBUFFER, m_renderbuffer);
    }
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*******************************************************************************/

void Framebuffer::gen_msaa_fbo(uint width, uint height, bool render_storage,
                               uint multisample_count)
{
    glGenFramebuffers(1, &m_multisample_buffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_multisample_buffer);

    glGenTextures(1, &m_multisample_texture);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_multisample_texture);

    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, multisample_count,
                            GL_RGB, width, height, GL_TRUE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D_MULTISAMPLE, m_multisample_texture, 0);

    if (render_storage)
    {
        glGenRenderbuffers(1, &m_multisample_renderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, m_multisample_renderbuffer);
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, multisample_count,
                                         GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                                  GL_RENDERBUFFER, m_multisample_renderbuffer);
    }

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        return;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

/*******************************************************************************/

Framebuffer::Framebuffer(uint width, uint height, bool render_storage)
{
    custom = true;
    m_width = width;
    m_height = height;
    base_renderstorage = render_storage;
    gen_fbo(width, height, render_storage);
}

/*******************************************************************************/

Framebuffer::Framebuffer(uint width, uint height, bool render_storage,
                         uint multisample_count)
{
    custom = true;
    m_width = width;
    m_height = height;
    msaa_renderstorage = render_storage;
    base_renderstorage = false;

    gen_fbo(width, height, false);
    gen_msaa_fbo(width, height, render_storage, multisample_count);
    m_multisampled = true;
}

/*******************************************************************************/

void Framebuffer::resize(int width, int height)
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, NULL);
    if (base_renderstorage)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width,
                              height);
    }

    if (m_multisampled)
    {
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_multisample_texture);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, width,
                                height, GL_TRUE);
        if (msaa_renderstorage)
        {
            glBindRenderbuffer(GL_RENDERBUFFER, m_multisample_renderbuffer);
            glRenderbufferStorageMultisample(
                GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, width, height);
        }
    }
    m_width = width;
    m_height = height;
}

/*******************************************************************************/

void Framebuffer::bind_texture(uint slot)
{
    if (m_multisampled)
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_multisample_buffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebuffer);
        glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height,
                          GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

/*******************************************************************************/

uint Framebuffer::get_texture()
{
    if (m_multisampled)
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, m_multisample_buffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebuffer);
        glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height,
                          GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }

    return m_texture;
}

/*******************************************************************************/

uint Framebuffer::get_handle()
{
    int x, y;
    x = Input::InputWindow::get_window_width();
    y = Input::InputWindow::get_window_height();
    if ((x != m_width || y != m_height) && custom)
    {
        resize(x, y);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    return m_multisampled ? m_multisample_buffer : m_framebuffer;
}

/*******************************************************************************/

Framebuffer::~Framebuffer() {}

} // namespace Render
} // namespace FW