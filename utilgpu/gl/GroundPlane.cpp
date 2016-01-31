#include "GroundPlane.h"

#include <vector>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/Group.h>
#include <utilgpu/gl/Shader.h>
#include <utilgpu/gl/Program.h>
#include <utilgpu/cpp/resource.h>

using namespace gl;

namespace util
{
GroundPlane::GroundPlane()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    GLuint buffer;

    std::vector<float> vertices = {0.0, 0.0,  0.0,  1.0, 1.0, 0.0,
                                   0.0, -1.0, -1.0, 0.0, 0.0, 1.0};

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    glDeleteBuffers(1, &buffer);
}

GroundPlane::~GroundPlane()
{
    glDeleteVertexArrays(1, &m_vao);
}

void GroundPlane::setViewProjection(const float* matrix)
{
    m_program->use();
    glUniformMatrix4fv((*m_program)["viewProjection"], 1, GL_FALSE, matrix);
}

void GroundPlane::addFragmentShader(Shader& shader)
{
    const Group<Shader> shaders(
        Shader::vertex(loadResource<utilgpu>("shader/groundplane.vert")),
        std::move(shader));
    m_program = std::make_unique<Program>(shaders);
}

void GroundPlane::draw()
{
    m_program->use();
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    glBindVertexArray(0);
}
}
