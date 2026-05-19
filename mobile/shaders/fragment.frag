#version 300 es

in float distance;

out vec4 fragColor;

uniform vec4 uColor;
uniform bool uIsPoint;

void main() {
    float period = 1.f + 1.f;
    if (mod(distance, period) > 1.f) discard;

    if (uIsPoint) {
        vec2 coord = gl_PointCoord - vec2(0.5);
        if (length(coord) > 0.5) discard;
    }

    fragColor = uColor;
}
