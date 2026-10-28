#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 instancePos;

uniform mat4 u_mvp;

out vec2 texCoord;

void main() {
    gl_Position = u_mvp * vec4(position + instancePos, 1);
    texCoord = aTexCoord;
}