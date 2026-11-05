#version 330

in vec2 texCoord;
out vec4 color;

uniform sampler2D u_texture;
uniform int debug;

void main() {
    vec4 textColor = texture(u_texture, texCoord);
    color = debug == 1 ? vec4(textColor.rg, 0.8, 1) : textColor;
}