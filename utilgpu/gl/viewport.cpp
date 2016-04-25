#include "viewport.h"

#include <cassert>

#include <glbinding/gl/gl.h>

namespace util
{
namespace viewport
{
using namespace gl;

Viewport::Viewport(const unsigned int& width, const unsigned int& height)
    : Viewport{0, 0, width, height}
{
}

Viewport::Viewport(const int& x, const int& y, const unsigned int& width,
                   const unsigned int& height)
    : x{x}, y{y}, width{width}, height{height}
{
}

Viewport get()
{
    GLint data[4];
    glGetIntegerv(GL_VIEWPORT, data);
    assert(data[2] >= 0 && data[3] >= 0);

    return {data[0], data[1], static_cast<unsigned int>(data[2]),
            static_cast<unsigned int>(data[3])};
}

void set(const Viewport& data)
{
    glViewport(data.x, data.y, data.width, data.height);
}

StateKeeper use(const Viewport& resolution)
{
    const auto old = get();
    set(resolution);
    return {[=]()
            {
                set(old);
            }};
}
}
}
