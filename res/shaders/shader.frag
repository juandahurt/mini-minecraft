#version 330

in vec2 texCoord;
out vec4 color;

uniform sampler2D u_texture;
uniform int debug;
uniform int u_faceDir;

// same order as the FaceDirection enum
const float FACE_BRIGHTNESS[6] = float[6](
    1.0,  // Y_UP
    0.5,  // Y_DOWN
    0.8,  // X_UP
    0.8,  // X_DOWN
    0.65, // Z_UP
    0.65  // Z_DOWN
);

void main() {
    vec4 textColor = texture(u_texture, texCoord);
    vec3 lit = textColor.rgb * FACE_BRIGHTNESS[u_faceDir];
    color = debug == 1 ? vec4(lit.rg, 0.8, 1) : vec4(lit, textColor.a);
}
