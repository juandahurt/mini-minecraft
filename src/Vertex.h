//
// Created by aureliano on 30/10/26.
//

#ifndef MINI_MINECRAFT_VERTEX_H
#define MINI_MINECRAFT_VERTEX_H
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Vertex {
private:
    glm::vec3 m_position;
    glm::vec2 m_texCoord;

public:
    Vertex(glm::vec3 position, glm::vec2 texCoord);
};


#endif //MINI_MINECRAFT_VERTEX_H
