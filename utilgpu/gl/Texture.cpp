#include "Texture.h"

#include <glbinding/gl/gl.h>
#include <utilgpu/qt/texture.h>

using namespace gl;

namespace util
{
Texture::Texture()
{
    glGenTextures(1, &m_texture);
    bind();
    parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
}

Texture::Texture(Texture&& old)
    : m_texture{old.m_texture}
    , m_format{old.m_format}
    , m_internalFormat{old.m_internalFormat}
    , m_type{old.m_type}
{
    old.m_texture = 0;
}

void Texture::parameter(GLenum type, GLenum parameter)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, type, static_cast<GLint>(parameter));
}

void Texture::load(const File& file)
{
    const auto glImage = loadImage(file.path);
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(m_internalFormat),
                 glImage.width(), glImage.height(), 0, m_format, m_type,
                 glImage.constBits());
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::size(const size_t& x, const size_t& y)
{
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(m_internalFormat), x, y,
                 0, m_format, m_type, nullptr);
}

GLuint Texture::get() const
{
    return m_texture;
}

void Texture::format(const GLenum& format, const GLenum& internalFormat,
                     const GLenum& type)
{
    m_format = format;
    m_internalFormat = internalFormat;
    m_type = type;
}
}
