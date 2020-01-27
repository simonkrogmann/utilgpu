#include "ShadowMap.h"

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/Group.h>
#include <utilgpu/cpp/resource.h>
#include <utilgpu/gl/Model.h>
#include <utilgpu/gl/Program.h>
#include <utilgpu/gl/Shader.h>
#include <utilgpu/gl/Texture.h>
#include <utilgpu/gl/viewport.h>
#include <glm/gtc/type_ptr.hpp>

using namespace gl;

namespace util
{
ShadowMap::ShadowMap(const size_t& width, const size_t& height)
    : m_fbo{width, height}, m_width{width}, m_height{height}
{
    auto depth = std::make_unique<Texture>();
    depth->format(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT32, GL_FLOAT);
    float color[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    depth->parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    depth->parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    m_fbo.attach(depth, GL_DEPTH_ATTACHMENT);

    const util::Group<Shader> shaders(
        Shader::vertex(loadResource<utilgpu>("shader/shadowmap.vert")),
        Shader::fragment(loadResource<utilgpu>("shader/shadowmap.frag")));
    m_program = std::make_unique<Program>(shaders);
}
ShadowMap::~ShadowMap() {}
void ShadowMap::draw(const std::vector<Model>& models,
                     const glm::mat4& lightViewProjection)
{
    auto keeper = m_fbo.use();
    auto keeper2 = viewport::use({m_width, m_height});
    glClear(GL_DEPTH_BUFFER_BIT);
    m_program->use();
    glUniformMatrix4fv((*m_program)["viewProjection"], 1, GL_FALSE,
                       glm::value_ptr(lightViewProjection));
    for (const auto& model : models)
    {
        glUniformMatrix4fv((*m_program)["model"], 1, GL_FALSE,
                           glm::value_ptr(model.matrix));
        model.drawable->draw();
    }
}
Texture* ShadowMap::get()
{
    return m_fbo.getDepth();
}

File ShadowMap::getShaderInclude()
{
    return loadResource<utilgpu>("shader/shadowmap_lookup.frag");
}
}  // namespace util
