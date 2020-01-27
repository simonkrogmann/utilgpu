#pragma once

#include <glbinding/gl/gl.h>

using namespace gl;

namespace util
{
class Drawable
{
public:
    Drawable();
    virtual ~Drawable();

    virtual void draw();

protected:
    GLuint m_vao;
};
}  // namespace util
