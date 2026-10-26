#version 330

layout(location = 0) in vec2 position;

uniform mat4 u_mvp;

void main() {
    gl_Position = u_mvp * vec4(position.xy, 0, 1);
}