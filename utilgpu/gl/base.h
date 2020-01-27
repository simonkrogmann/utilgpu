#pragma once

#include <string>

#include <glbinding/ProcAddress.h>
#include <glbinding/gl/gl.h>

namespace util
{
using namespace gl;

void glInitialize(glbinding::GetProcAddress context);
void glContextInfo();

GLint glGetInteger(const GLenum& symbol);

template <typename T>
GLint glLength(const T& object)
{
    return static_cast<GLint>(object.size());
}

bool glExtensionSupported(const std::string& extension);
std::string glslVersion();

std::string toString(const GLubyte* glString);
}  // namespace util
