#pragma once

#include <map>
#include <string>
#include <vector>

#include <glbinding/gl/gl.h>

using namespace gl;

namespace util
{
class File;

class Shader
{
public:
    static std::string includeString(const std::string& name);
    static std::string textureString(const std::string& name);

    static Shader vertex(const File& file,
                         const std::vector<File>& includes = {});
    static Shader geometry(const File& file,
                           const std::vector<File>& includes = {});
    static Shader fragment(const File& file,
                           const std::vector<File>& includes = {});
    static Shader compute(const File& file,
                          const std::vector<File>& includes = {});

    Shader(Shader&& old);
    Shader(const Shader&) = delete;
    Shader(const std::string& name, const std::string& source,
           const GLenum& type, const std::vector<File>& includes = {});
    ~Shader();

    bool isCompiled() const;
    void printCompilationError() const;
    GLuint get() const;
    std::string name() const;

private:
    void includeShader(const std::string& name, const std::string& source);
    void compileShader(const std::string& source);

    std::string m_name;
    GLuint m_shader;
    std::map<std::string, std::string> m_includes;
};
}
