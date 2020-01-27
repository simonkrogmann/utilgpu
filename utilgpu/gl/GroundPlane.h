#pragma once

#include <memory>

#include <utilgpu/gl/Drawable.h>

namespace util
{
class Shader;

class GroundPlane : public Drawable
{
public:
    GroundPlane();
    virtual ~GroundPlane();
    virtual void draw() override;
    Shader getVertexShader();
};
}  // namespace util
