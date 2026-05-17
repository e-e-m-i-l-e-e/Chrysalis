#version 300 es

layout(location = 0) in vec2 position;
layout(location = 1) in float distance;

uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * vec4(position, 0.0, 1.0);
}