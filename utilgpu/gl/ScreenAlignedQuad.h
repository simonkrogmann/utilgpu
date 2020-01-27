#pragma once

#include <utilgpu/gl/Drawable.h>

namespace util
{
class ScreenAlignedQuad : public Drawable
{
public:
    ScreenAlignedQuad();
    virtual ~ScreenAlignedQuad();

    virtual void draw() override;
};
}  // namespace util
