//
// Created by aureliano on 24/10/26.
//

#include "Renderer.h"

void GLClearError() {
    while (glGetError() != GL_NO_ERROR) {}
}

void GLLogCall(const char* function, const char* file, const int line) {
    while (const GLenum error = glGetError()) {
        std::cerr << "[OpenGL error]: (" << error << ")" << function << " " << file << ":" << line << std::endl;
    }
}