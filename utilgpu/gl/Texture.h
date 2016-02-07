#pragma once

#include <string>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/file.h>

using namespace gl;

namespace util
{
class Texture
{
public:
    Texture();
    Texture(Texture&& old);
    Texture(const Texture&) = delete;
    ~Texture();

    void bind() const;
    void load(const File& file);
    void size(const size_t& x, const size_t& y);
    void parameter(GLenum type, GLenum parameter);
    void format(const GLenum& format, const GLenum& internalFormat,
                const GLenum& type);
    GLuint get() const;

private:
    GLuint m_texture;
    GLenum m_format = GL_RGBA;
    GLenum m_internalFormat = GL_RGBA8;
    GLenum m_type = GL_UNSIGNED_BYTE;
};
}
