//
// Created by aureliano on 27/10/26.
//

#include "Camera.h"

#include <glm/ext/matrix_transform.hpp>


Camera::Camera() {
    m_position = glm::vec3(0.0f, 5.0f, -3.0f);
    m_front = glm::vec3(0.0f, 0.0f, 1.0f);
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_speed = 0.5;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::vec3 Camera::getPosition() {
    return m_position;
}

void Camera::setPosition(glm::vec3 position) {
    m_position = position;
}

glm::vec3 Camera::getFront() {
    return m_front;
}

void Camera::setFront(glm::vec3 front) {
    m_front = front;
}

glm::vec3 Camera::getUp() {
    return m_up;
}

void Camera::setUp(glm::vec3 up) {
    m_up = up;
}

float Camera::getSpeed() const {
    return m_speed;
}

void Camera::setSpeed(float speed) {
    m_speed = speed;
}
