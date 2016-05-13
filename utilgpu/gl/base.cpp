#include "base.h"

#include <iostream>
#include <map>
#include <string>

#include <glbinding/Binding.h>
#include <glbinding/callbacks.h>
#include <glbinding/gl/gl.h>

namespace util
{
using namespace gl;

void glInitialize()
{
    glbinding::Binding::initialize(false);
    glbinding::setCallbackMaskExcept(
        glbinding::CallbackMask::After | glbinding::CallbackMask::Parameters,
        {"glGetError"});
    glbinding::setAfterCallback([](const glbinding::FunctionCall& call) {
        const auto error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cout << error << " in " << call.function->name()
                      << " with parameters:" << std::endl;
            for (const auto& parameter : call.parameters)
            {
                std::cout << "    " << parameter->asString() << std::endl;
            }
        }
    });
}

void glContextInfo()
{
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

GLint glGetInteger(const GLenum& symbol)
{
    GLint value;
    glGetIntegerv(symbol, &value);
    return value;
}

std::string toString(const GLubyte* glString)
{
    return reinterpret_cast<char const*>(glString);
}

bool glExtensionSupported(const std::string& extension)
{
    const auto extensionsRaw = glGetString(GL_EXTENSIONS);
    if (extensionsRaw == NULL)
    {
        glGetError();
        return false;
    }
    const std::string extensions = toString(glGetString(GL_EXTENSIONS));
    return extensions.find(extension) != std::string::npos;
}

std::string glslVersion()
{
    int major = 0;
    int minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    const std::string glVersion = std::to_string(major) + std::to_string(minor);
    const std::map<std::string, std::string> glslVersionMapping{
        {"20", "110"}, {"21", "120"}, {"30", "130"},
        {"31", "140"}, {"32", "150"},
    };
    if (glslVersionMapping.find(glVersion) != glslVersionMapping.end())
    {
        return glslVersionMapping.at(glVersion);
    }
    return glVersion + "0";
}
}
