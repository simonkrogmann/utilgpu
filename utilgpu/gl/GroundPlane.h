#pragma once

#include <memory>

#include <utilgpu/gl/Drawable.h>

namespace util
{
class Shader;
class Program;

class GroundPlane : public Drawable
{
public:
    GroundPlane();
    virtual ~GroundPlane();

    void addFragmentShader(Shader& shader);

    void setViewProjection(const float* matrix);
    virtual void draw() override;

private:
    std::unique_ptr<Program> m_program;
};
}
