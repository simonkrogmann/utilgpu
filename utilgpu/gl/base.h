#pragma once

#include <string>

#include <glbinding/gl/gl.h>

namespace util
{
using namespace gl;

GLint glGetInteger(const GLenum& symbol);

template <typename T>
GLint glLength(const T& object)
{
    return static_cast<GLint>(object.size());
}

void glContextInfo();

bool glExtensionSupported(const std::string& extension);
std::string glslVersion();

std::string toString(const GLubyte* glString);
}
