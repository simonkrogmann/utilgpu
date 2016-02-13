#pragma once

#include <vector>

#include <glm/fwd.hpp>
#include <utilgpu/gl/Framebuffer.h>

namespace util
{
class Model;

class Program;

class ShadowMap
{
public:
    ShadowMap(const size_t& width = 1024, const size_t& height = 1024);
    ~ShadowMap();
    void draw(const std::vector<Model>& models,
              const glm::mat4& lightViewProjection);
    Texture* get();

private:
    Framebuffer m_fbo;
    std::unique_ptr<Program> m_program;
    size_t m_width;
    size_t m_height;
};
}
