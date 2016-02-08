#include "Framebuffer.h"

#include <iostream>
#include <vector>
#include <cassert>
#include <memory>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/StateKeeper.h>
#include <utilgpu/gl/base.h>
#include <utilgpu/gl/viewport.h>
#include <utilgpu/gl/Texture.h>
#include <utilgpu/qt/texture.h>

using namespace gl;

namespace util
{
std::unique_ptr<Framebuffer> Framebuffer::None()
{
    return std::make_unique<Framebuffer>();
}

std::unique_ptr<Framebuffer> Framebuffer::Simple(const size_t& width,
                                                 const size_t& height)
{
    auto color = std::make_unique<Texture>();
    auto depth = std::make_unique<Texture>();
    depth->format(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT32, GL_FLOAT);
    auto fbo = std::make_unique<Framebuffer>(width, height);
    fbo->attach(color, GL_COLOR_ATTACHMENT0);
    fbo->attach(depth, GL_DEPTH_ATTACHMENT);
    return fbo;
}

Framebuffer::Framebuffer()
    : m_framebuffer{0}, m_width{0}, m_height{0}, m_useNone{true}
{
}

Framebuffer::Framebuffer(const size_t& width, const size_t& height)
    : m_framebuffer{0}, m_width{width}, m_height{height}, m_useNone{false}
{
    glGenFramebuffers(1, &m_framebuffer);

    resize(width, height);
}

Framebuffer::~Framebuffer()
{
    if (!m_useNone)
    {
        glDeleteFramebuffers(1, &m_framebuffer);
    }
}

Framebuffer::Framebuffer(Framebuffer&& old)
    : m_framebuffer{old.m_framebuffer}
    , m_width{old.m_width}
    , m_height{old.m_height}
{
    old.m_framebuffer = 0;
    for (auto& texture : old.m_textures)
    {
        m_textures.emplace(texture.first, std::move(texture.second));
    }
}

void Framebuffer::attach(std::unique_ptr<Texture>& texture,
                         const GLenum& target)
{
    const auto keeper = use();
    glFramebufferTexture2D(GL_FRAMEBUFFER, target, GL_TEXTURE_2D,
                           texture->get(), 0);
    texture->size(m_width, m_height);
    m_textures.emplace(target, std::move(texture));
}

void Framebuffer::check()
{
    const auto keeper = use();
    auto framebufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (framebufferStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Framebuffer is incomplete: " << framebufferStatus
                  << std::endl;
    }
}

StateKeeper Framebuffer::use(const GLenum& mode) const
{
    if (m_useNone)
    {
        return {[]()
                {
                }};
    }
    const auto old = glGetInteger(GL_FRAMEBUFFER_BINDING);
    glBindFramebuffer(mode, m_framebuffer);
    return {[=]()
            {
                glBindFramebuffer(mode, old);
            }};
}

void Framebuffer::save(const std::string& filename)
{
    assert(!m_useNone);
    const auto keeper = use(GL_READ_FRAMEBUFFER);
    std::vector<unsigned char> imageData(m_width * m_height * 4);
    glReadPixels(0, 0, m_width, m_height, GL_BGRA, GL_UNSIGNED_BYTE,
                 &imageData[0]);
    saveImage(imageData, m_width, m_height, filename);
}

void Framebuffer::resize(const size_t& width, const size_t& height)
{
    if (m_useNone)
    {
        return;
    }
    if (m_width == width && m_height == height)
    {
        return;
    }
    m_width = width;
    m_height = height;

    for (auto& texture : m_textures)
    {
        texture.second->size(m_width, m_height);
    }
}

void Framebuffer::resize(const viewport::Viewport& viewport)
{
    resize(viewport.width, viewport.height);
}

GLuint Framebuffer::get() const
{
    return m_framebuffer;
}

Texture* Framebuffer::getColor() const
{
    return getTexture(GL_COLOR_ATTACHMENT0);
}

Texture* Framebuffer::getDepth() const
{
    return getTexture(GL_DEPTH_ATTACHMENT);
}

Texture* Framebuffer::getTexture(const GLenum& target) const
{
    return (*m_textures.find(target)).second.get();
}
}
