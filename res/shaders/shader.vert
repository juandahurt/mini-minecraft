#version 330

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 u_mvp;

out vec2 texCoord;

void main() {
    gl_Position = u_mvp * vec4(position.xy, 0, 1);
    texCoord = aTexCoord;
}