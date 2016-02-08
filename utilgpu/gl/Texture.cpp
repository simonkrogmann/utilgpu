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
    m_width = glImage.width();
    m_height = glImage.height();
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::size(const size_t& width, const size_t& height)
{
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(m_internalFormat), width,
                 height, 0, m_format, m_type, nullptr);
    m_width = width;
    m_height = height;
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

void Texture::save(const std::string& filename)
{
    std::map<GLenum, int> channels{
        {GL_DEPTH_COMPONENT, 1}, {GL_RGBA, 4}, {GL_RGB, 3}, {GL_RED, 1}};
    bind();
    std::vector<unsigned char> imageData(m_width * m_height * 4);
    glGetTexImage(GL_TEXTURE_2D, 0, m_format, GL_UNSIGNED_BYTE, &imageData[0]);
    saveImage(imageData, m_width, m_height, filename, channels.at(m_format));
}
}
