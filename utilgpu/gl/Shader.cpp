#include "Shader.h"

#include <iostream>
#include <memory>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/file.h>
#include <utilgpu/cpp/str.h>
#include <utilgpu/gl/base.h>

using namespace gl;
namespace util
{
unsigned int Shader::id = 0;
std::string Shader::uniqueId()
{
    return std::to_string(++id);
}

std::string Shader::includeString(const std::string& name)
{
    return "#include \"/" + name + "\"\n";
}

std::string Shader::textureString(const std::string& name)
{
    return "uniform sampler2D " + name + ";\n";
}

std::string Shader::idString()
{
    return "const int shader_id = " + uniqueId() + ";\n";
}

Shader Shader::vertex(const File& file, const std::vector<File>& includes)
{
    return Shader(file.name, file.content(), GL_VERTEX_SHADER, includes);
}

Shader Shader::geometry(const File& file, const std::vector<File>& includes)
{
    return Shader(file.name, file.content(), GL_GEOMETRY_SHADER, includes);
}

Shader Shader::fragment(const File& file, const std::vector<File>& includes)
{
    return Shader(file.name, file.content(), GL_FRAGMENT_SHADER, includes);
}

Shader Shader::compute(const File& file, const std::vector<File>& includes)
{
    return Shader(file.name, file.content(), GL_COMPUTE_SHADER, includes);
}

Shader::Shader(const std::string& name, const std::string& source,
               const GLenum& type, const std::vector<File>& includes)
    : m_name{name}, m_shader{0}
{
    auto shaderSource = source;
    const static auto version = glslVersion();
    replace(shaderSource, "#version 330", "#version " + version);

    if (contains(shaderSource, "//id"))
    {
        const auto idReplacement = (includes.size() > 0) ? idString() : "";
        replace(shaderSource, "//id", idReplacement);
    }

    // handle includes
    for (const auto& include : includes)
    {
        includeShader("/" + include.name, include.content());
    }

    m_shader = glCreateShader(type);
    compileShader(shaderSource);
    if (!isCompiled())
    {
        printCompilationError();
    }
}

void Shader::includeShader(const std::string& name, const std::string& source)
{
    m_includes[name] = source;
}

void Shader::compileShader(const std::string& source)
{
    auto uploadSource = source;
    for (const auto& include : m_includes)
    {
        const auto directive = "#include \"" + include.first + "\"";
        replace(uploadSource, directive, include.second);
    }
    const auto shaderCString = uploadSource.c_str();
    const auto shaderLength = glLength(uploadSource);
    glShaderSource(m_shader, 1, &shaderCString, &shaderLength);
    glCompileShader(m_shader);
}

Shader::Shader(Shader&& old) : m_name{old.m_name}, m_shader{old.m_shader}
{
    old.m_shader = 0;
}

Shader::~Shader()
{
    glDeleteShader(m_shader);
}

GLuint Shader::get() const
{
    return m_shader;
}

std::string Shader::name() const
{
    return m_name;
}

bool Shader::isCompiled() const
{
    GLint isCompiled;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &isCompiled);
    return static_cast<GLboolean>(isCompiled) != GL_FALSE;
}

void Shader::printCompilationError() const
{
    std::cout << "Compilation failed for " << m_name << ":" << std::endl;
    GLint length;
    glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &length);
    std::unique_ptr<char> infoLog{new char[length + 1]};
    glGetShaderInfoLog(m_shader, length, NULL, infoLog.get());
    std::cout << infoLog.get() << std::endl;
}
}
