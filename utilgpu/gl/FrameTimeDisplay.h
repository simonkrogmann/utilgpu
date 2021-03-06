#pragma once

#include <chrono>
#include <memory>

#include <utilgpu/gl/ScreenAlignedQuad.h>

namespace util
{
class Program;
namespace viewport
{
struct Viewport;
}

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
}  // namespace util
