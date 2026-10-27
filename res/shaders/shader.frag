#version 330

in vec2 texCoord;
out vec4 color;

uniform sampler2D u_texture;

void main() {
    color = texture(u_texture, texCoord);
}