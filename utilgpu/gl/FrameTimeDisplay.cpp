#include "FrameTimeDisplay.h"

#include <chrono>
#include <memory>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/Group.h>
#include <utilgpu/cpp/numeric.h>
#include <utilgpu/cpp/resource.h>
#include <utilgpu/gl/Program.h>
#include <utilgpu/gl/Shader.h>
#include <utilgpu/gl/viewport.h>

using namespace gl;

namespace util
{
FrameTimeDisplay::FrameTimeDisplay()
{
}

FrameTimeDisplay::~FrameTimeDisplay()
{
}

void FrameTimeDisplay::init()
{
    reset();
    const util::Group<Shader> shaders(
        Shader::vertex(loadResource<utilgpu>("shader/screenalignedquad.vert")),
        Shader::fragment(loadResource<utilgpu>("shader/onscreendisplay.frag")));
    m_program = std::make_unique<Program>(shaders);
}

void FrameTimeDisplay::reset()
{
    m_frames = 0;
    m_start = std::chrono::steady_clock::now();
}

void FrameTimeDisplay::render(const viewport::Viewport&)
{
    if (!m_program->isLinked())
    {
        return;
    }
    std::chrono::duration<double> diff =
        std::chrono::steady_clock::now() - m_start;
    if (diff.count() > 1.0)
    {
        m_value = 1000.0 / std::max(m_frames, 1u);
        reset();
    }
    ++m_frames;

    std::vector<int> number = toDigits(static_cast<unsigned int>(m_value));
    auto numDigits = static_cast<unsigned int>(number.size());
    number.resize(10, 0);

    auto keeper = viewport::use(viewport::Viewport{20 * numDigits, 40});
    m_program->use();
    glUniform1iv((*m_program)["number"], 10, number.data());
    glUniform1ui((*m_program)["numDigits"], numDigits);
    m_screen.draw();
}
}
