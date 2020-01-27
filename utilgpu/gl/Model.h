#pragma once

#include <utilgpu/gl/Drawable.h>
#include <glm/mat4x4.hpp>

namespace util
{
struct Model
{
    Drawable* drawable;
    glm::mat4 matrix;
};
}  // namespace util
