#version 140
#extension GL_ARB_explicit_attrib_location : enable

layout(location = 0)in vec2 vertex;

out vec2 position;

uniform mat4 viewProjection;

void main() {
    vec2 distant_vertex = vertex * 1.0 / 0.000001;
    gl_Position = viewProjection * vec4(distant_vertex, 0.0, 1.0);
    position = distant_vertex;
}
