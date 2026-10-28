//
// Created by aureliano on 24/10/26.
//

#ifndef MINI_MINECRAFT_VERTEXARRAY_H
#define MINI_MINECRAFT_VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
private:
    unsigned int m_id;
    unsigned int m_attribIndex = 0;
public:
    VertexArray();
    ~VertexArray();

    void bind();
    void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    void addInstancedBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};


#endif //MINI_MINECRAFT_VERTEXARRAY_H
