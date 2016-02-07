#pragma once

#include <string>
#include <map>
#include <memory>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/StateKeeper.h>
#include <utilgpu/gl/viewport.h>

using namespace gl;

namespace util
{
class Texture;

class Framebuffer
{
public:
    static std::unique_ptr<Framebuffer> None();
    static std::unique_ptr<Framebuffer> Simple(const unsigned int& width,
                                               const unsigned int& height);
    Framebuffer();
    Framebuffer(const unsigned int& m_width, const unsigned int& height);
    Framebuffer(Framebuffer&& old);
    Framebuffer(const Framebuffer&) = delete;
    ~Framebuffer();

    void attach(std::unique_ptr<Texture>& texture, const GLenum& target);
    void check();
    StateKeeper use(const GLenum& mode = GL_FRAMEBUFFER) const;
    void resize(const unsigned int& m_width, const unsigned int& height);
    void resize(const viewport::Viewport& viewport);
    void save(const std::string& filename);

    GLuint get() const;
    Texture* getColor() const;
    Texture* getDepth() const;
    Texture* getTexture(const GLenum& target) const;

private:
    GLuint m_framebuffer;
    unsigned int m_width;
    unsigned int m_height;
    bool m_useNone;
    std::map<GLenum, std::unique_ptr<Texture>> m_textures;
};
}
