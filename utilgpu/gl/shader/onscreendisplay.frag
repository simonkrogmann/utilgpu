#version 140
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0) out vec4 color;
in vec2 position;

uniform uint numDigits;
uniform int number[10];

const int[10 * 7] table = int[](
    1, 1, 1, 1, 1, 0, 1,
    0, 0, 1, 1, 0, 0, 0,
    0, 1, 1, 0, 1, 1, 1,
    0, 0, 1, 1, 1, 1, 1,
    1, 0, 1, 1, 0, 1, 0,
    1, 0, 0, 1, 1, 1, 1,
    1, 1, 0, 1, 1, 1, 1,
    0, 0, 1, 1, 0, 0, 1,
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
}
