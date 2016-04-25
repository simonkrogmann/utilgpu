#pragma once

#include <glm/mat4x4.hpp>
#include <utilgpu/gl/Drawable.h>

namespace util
{
struct Model
{
    Drawable* drawable;
    glm::mat4 matrix;
};
}
