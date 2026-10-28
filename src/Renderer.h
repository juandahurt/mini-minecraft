//
// Created by aureliano on 24/10/26.
//

#ifndef MINI_MINECRAFT_RENDERER_H
#define MINI_MINECRAFT_RENDERER_H

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif
#include <iostream>

#include "IndexBuffer.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"

#define GLCall(x) GLClearError(); x; GLLogCall(#x, __FILE__, __LINE__);

void GLClearError();
void GLLogCall(const char* function, const char* file, const int line);

class Renderer {
public:
    void clear(float r, float g, float b, float a);
    void draw(const IndexBuffer& indexBuffer, const VertexBuffer& vertexBuffer, const ShaderProgram& shaderProgram) const;
    void drawInstanced(const IndexBuffer& indexBuffer, const VertexBuffer& vertexBuffer, const ShaderProgram& shaderProgram, unsigned int count) const;
};


#endif //MINI_MINECRAFT_RENDERER_H
