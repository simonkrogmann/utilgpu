#pragma once

#include <chrono>
#include <memory>

#include <utilgpu/gl/Program.h>
#include <utilgpu/gl/ScreenAlignedQuad.h>
#include <utilgpu/gl/viewport.h>

namespace util
{
class FrameTimeDisplay
{
public:
    FrameTimeDisplay();
    virtual ~FrameTimeDisplay();

    virtual void init();
    void render(const viewport::Viewport&);

private:
    void reset();

    ScreenAlignedQuad m_screen;
    std::unique_ptr<Program> m_program;
    unsigned int m_frames = 0;
    float m_value = 0;
    std::chrono::time_point<std::chrono::steady_clock> m_start;
};
}
