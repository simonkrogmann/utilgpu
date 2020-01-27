#pragma once

#include <string>

#include <glbinding/gl/gl.h>

using namespace gl;

namespace util
{
class File;

class Texture
{
public:
    Texture();
    Texture(Texture&& old);
    Texture(const Texture&) = delete;
    ~Texture();

    void bind() const;
    void load(const File& file);
    void size(const size_t& width, const size_t& height);
    void setData(const size_t& width, const size_t& height, const GLvoid* data);
    void parameter(GLenum type, GLenum parameter);
    void format(const GLenum& format, const GLenum& internalFormat,
                const GLenum& type);
    GLuint get() const;
    void save(const std::string& filename);
    void generateMipMap();

private:
    GLuint m_texture;
    GLenum m_format = GL_RGBA;
    GLenum m_internalFormat = GL_RGBA8;
    GLenum m_type = GL_UNSIGNED_BYTE;
    size_t m_width = 0;
    size_t m_height = 0;
};
}  // namespace util
