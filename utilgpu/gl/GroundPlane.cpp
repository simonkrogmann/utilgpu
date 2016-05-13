#include "GroundPlane.h"

#include <vector>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/resource.h>
#include <utilgpu/gl/Shader.h>

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

Shader GroundPlane::getVertexShader()
{
    return Shader::vertex(loadResource<utilgpu>("shader/groundplane.vert"));
}

void GroundPlane::draw()
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    glBindVertexArray(0);
}
}
