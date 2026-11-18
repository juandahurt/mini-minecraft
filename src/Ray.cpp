//
// Created by aureliano on 10/11/26.
//

#include "Ray.h"

Ray::Ray(const glm::vec3& position, const glm::vec3& direction) : m_position(position), m_direction(direction) {}

glm::vec3 Ray::pointAt(float t) const {
    return m_position + m_direction * t;
}
