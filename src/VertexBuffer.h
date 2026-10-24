//
// Created by aureliano on 24/10/26.
//

#ifndef MINI_MINECRAFT_VERTEXBUFFER_H
#define MINI_MINECRAFT_VERTEXBUFFER_H

class VertexBuffer {
private:
    unsigned int m_id;
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const;
};


#endif //MINI_MINECRAFT_VERTEXBUFFER_H
