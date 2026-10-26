//
// Created by aureliano on 24/10/26.
//

#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout(): m_stride(0) {}
VertexBufferLayout::~VertexBufferLayout() {}

unsigned int VertexBufferLayout::getStride() const {
    return m_stride;
}

const std::vector<VertexBufferElement>& VertexBufferLayout::getElements() const {
    return m_elements;
}
