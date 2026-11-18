//
// Created by aureliano on 10/11/26.
//

#ifndef MINI_MINECRAFT_RAY_H
#define MINI_MINECRAFT_RAY_H
#include <glm/vec3.hpp>


class Ray {
    glm::vec3 m_position;
    glm::vec3 m_direction;
public:
    Ray(const glm::vec3& position, const glm::vec3& direction);
    glm::vec3 pointAt(float t) const;
};


#endif //MINI_MINECRAFT_RAY_H
