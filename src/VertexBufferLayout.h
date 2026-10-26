//
// Created by aureliano on 24/10/26.
//

#ifndef MINI_MINECRAFT_VERTEXBUFFERLAYOUT_H
#define MINI_MINECRAFT_VERTEXBUFFERLAYOUT_H
#include <vector>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

struct VertexBufferElement {
    unsigned int count;
    unsigned int type;
    bool normalized;

    static unsigned int getSize(unsigned int type) {
        switch (type) {
            case GL_FLOAT: return sizeof(GLfloat);
            default: return 0;
        }
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_elements;
    unsigned int m_stride;
public:
    VertexBufferLayout();
    ~VertexBufferLayout();

    template<typename T>
    void push(unsigned int count) {}

    template<>
    void push<float>(unsigned int count) {
        m_elements.push_back(
            {
                count,
                GL_FLOAT,
                false
            }
        );
        m_stride += count * VertexBufferElement::getSize(GL_FLOAT);
    }

    unsigned int getStride() const;
    const std::vector<VertexBufferElement>& getElements() const;
};


#endif //MINI_MINECRAFT_VERTEXBUFFERLAYOUT_H
