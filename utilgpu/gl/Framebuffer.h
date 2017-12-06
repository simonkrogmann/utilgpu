#pragma once

#include <map>
#include <memory>
#include <string>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/StateKeeper.h>

using namespace gl;

namespace util
{
class Texture;
namespace viewport
{
struct Viewport;
}

class Framebuffer
{
public:
    static std::unique_ptr<Framebuffer> None();
    static std::unique_ptr<Framebuffer> Simple(const size_t& width,
                                               const size_t& height);
    Framebuffer();
    Framebuffer(const size_t& m_width, const size_t& height);
    Framebuffer(Framebuffer&& old);
    Framebuffer(const Framebuffer&) = delete;
    ~Framebuffer();

    void attach(std::unique_ptr<Texture>& texture, const GLenum& target);
    void check();
    StateKeeper use(const GLenum& mode = GL_FRAMEBUFFER) const;
    void resize(const size_t& m_width, const size_t& height);
    void resize(const viewport::Viewport& viewport);
    void save(const std::string& filename);

    GLuint get() const;
    Texture* getColor() const;
    Texture* getDepth() const;
    Texture* getTexture(const GLenum& target) const;
    std::unique_ptr<Texture>&& stealTexture(const GLenum& target);

private:
    GLuint m_framebuffer;
    size_t m_width;
    size_t m_height;
    bool m_useNone;
    std::map<GLenum, std::unique_ptr<Texture>> m_textures;
};
}
