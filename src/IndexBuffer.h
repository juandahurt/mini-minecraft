//
// Created by aureliano on 24/10/26.
//

#ifndef MINI_MINECRAFT_INDEXBUFFER_H
#define MINI_MINECRAFT_INDEXBUFFER_H


class IndexBuffer {
private:
    unsigned int m_id;
    unsigned int m_count;
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    unsigned int getCount() const;
};


#endif //MINI_MINECRAFT_INDEXBUFFER_H
