#include "FrameTimeDisplay.h"

#include <chrono>
#include <memory>

#include <glbinding/gl/gl.h>
#include <utilgpu/cpp/numeric.h>
#include <utilgpu/gl/Program.h>
#include <utilgpu/gl/Shader.h>
#include <utilgpu/cpp/Group.h>

using namespace gl;
namespace
{
std::string screenalignedquad = R"(#version 140
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0)in vec2 vertex;

out vec2 position;

void main() {
    gl_Position = vec4(vertex, 0.0, 1.0);
    position = vertex / 2.0 + 0.5;
})";

std::string onscreendisplay = R"(#version 140
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) out vec4 color;
in vec2 position;

uniform uint numDigits;
uniform int number[10];

const int[10 * 7] table = int[](
    1, 1, 1, 1, 1, 1, 1,
    0, 0, 1, 1, 0, 0, 0,
    0, 1, 1, 0, 1, 1, 1,
    0, 0, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 0,
    1, 0, 0, 1, 1, 1, 1,
    1, 1, 0, 1, 1, 1, 1,
    0, 0, 1, 1, 1, 0, 0,
    1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 1, 1, 1
);

void main() {
    int place = int(floor(position.x * numDigits));
    int digit = number[place];
    vec2 uv = vec2(fract(position.x * numDigits), position.y);
    int segment = -1;
    if (uv.x < 0.2)
    {
        if (uv.y > 0.5) segment = 0;
        else segment = 1;
    }
    else if (uv.x > 0.8)
    {
        if (uv.y > 0.5) segment = 2;
        else segment = 3;
    }
    if (uv.y < 0.15) segment = 4;
    if (uv.y > 0.45 && uv.y < 0.55) segment = 5;
    if (uv.y > 0.85)  segment = 6;


    // border
    uv -= 0.5;
    uv = abs(uv);
    bool border = (max(uv.x, uv.y) >= 0.45);


    if (segment == -1 || border)
    {
    color = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else
    {
    color = vec4(0.0, 0.0, 1.0, 1.0);
    color = table[digit * 7 + segment] * vec4(0.2, 0.7, 0.1, 1.0);
    }
})";
}

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
        Shader("screenalignedquad.yert", screenalignedquad, GL_VERTEX_SHADER,
               {}),
        Shader("onscreendisplay.frag", onscreendisplay, GL_FRAGMENT_SHADER,
               {}));
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
        m_value = 1000.0 / m_frames;
        reset();
    }
    ++m_frames;

    std::vector<int> number = toDigits(static_cast<unsigned int>(m_value));
    auto numDigits = static_cast<unsigned int>(number.size());
    number.resize(10, 0);

    auto keeper = viewport::use(viewport::Viewport{0, 0, 20 * numDigits, 40});
    m_program->use();
    glUniform1iv((*m_program)["number"], 10, number.data());
    glUniform1ui((*m_program)["numDigits"], numDigits);
    m_screen.draw();
}
}
