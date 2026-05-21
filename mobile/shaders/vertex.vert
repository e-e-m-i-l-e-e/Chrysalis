#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in float distance_;

uniform mat4 uProjection;
uniform float uPointRadius;

out float distance;

void main() {
    distance = distance_;
    gl_PointSize = uPointRadius * 2.0;
    gl_Position = uProjection * vec4(position, 0.0, 1.0);
}