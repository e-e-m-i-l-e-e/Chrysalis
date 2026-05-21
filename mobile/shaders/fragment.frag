#version 330 core

in float distance;

out vec4 fragColor;

uniform vec4 uColor;
uniform float uPointRadius;

void main() {
    if (mod(distance, 1.f) > 0.5f) discard;
    if (uPointRadius > 0. && length(gl_PointCoord - vec2(0.5)) > 0.5) discard;
    fragColor = uColor;
}
