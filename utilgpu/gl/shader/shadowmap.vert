#version 330
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0)in vec3 vertex;

uniform mat4 model;
uniform mat4 viewProjection;

void main() {
    gl_Position = viewProjection * model * vec4(vertex, 1.0);
}
