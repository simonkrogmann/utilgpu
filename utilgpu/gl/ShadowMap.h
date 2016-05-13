#pragma once

#include <vector>

#include <utilgpu/gl/Framebuffer.h>
#include <glm/fwd.hpp>

namespace util
{
class Model;
class Program;
class File;

class ShadowMap
{
public:
    ShadowMap(const size_t& width = 1024, const size_t& height = 1024);
    ~ShadowMap();
    void draw(const std::vector<Model>& models,
              const glm::mat4& lightViewProjection);
    Texture* get();
    File getShaderInclude();

private:
    Framebuffer m_fbo;
    std::unique_ptr<Program> m_program;
    size_t m_width;
    size_t m_height;
};
}
