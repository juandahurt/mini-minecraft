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

void Renderer::clear(float r, float g, float b, float a) {
    GLCall(glClearColor(r, g, b, a));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::draw(const IndexBuffer &indexBuffer, const VertexBuffer &vertexBuffer, const ShaderProgram &shaderProgram) const {
    vertexBuffer.bind();
    indexBuffer.bind();
    shaderProgram.bind();
    GLCall(glDrawElements(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::drawInstanced(const IndexBuffer &indexBuffer, const VertexBuffer &vertexBuffer, const ShaderProgram &shaderProgram, unsigned int count) const {
    vertexBuffer.bind();
    indexBuffer.bind();
    shaderProgram.bind();
    GLCall(glDrawElementsInstanced(GL_TRIANGLES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr, count));
}

void Renderer::drawLines(const IndexBuffer &indexBuffer, const VertexBuffer &vertexBuffer, const ShaderProgram &shaderProgram) const {
    vertexBuffer.bind();
    indexBuffer.bind();
    shaderProgram.bind();
    GLCall(glDrawElements(GL_LINES, indexBuffer.getCount(), GL_UNSIGNED_INT, nullptr));
}
