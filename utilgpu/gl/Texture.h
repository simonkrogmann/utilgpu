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
    Texture(const File& file);
    Texture(Texture&& old);
    Texture(const Texture&) = delete;
    ~Texture();

    void bind() const;
    void load();
    GLuint get() const { return m_texture; }
    std::string name() const { return m_file.name; }
private:
    File m_file;
    GLuint m_texture;
};
}
