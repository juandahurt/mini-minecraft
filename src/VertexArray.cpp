//
// Created by aureliano on 24/10/26.
//

#include "VertexArray.h"

#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &m_id));
}

VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &m_id));
}

void VertexArray::bind() {
    GLCall(glBindVertexArray(m_id));
}

void VertexArray::addBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (const auto& element : elements) {
        GLCall(glEnableVertexAttribArray(m_attribIndex));
        GLCall(glVertexAttribPointer(m_attribIndex, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
        offset += element.count * VertexBufferElement::getSize(element.type);
        m_attribIndex++;
    }
}

void VertexArray::addInstancedBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout) {
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (const auto& element : elements) {
        GLCall(glEnableVertexAttribArray(m_attribIndex));
        GLCall(glVertexAttribPointer(m_attribIndex, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
        GLCall(glVertexAttribDivisor(m_attribIndex, 1));
        offset += element.count * VertexBufferElement::getSize(element.type);
        m_attribIndex++;
    }
}
