//
// Created by aureliano on 5/11/26.
//

#include "Player.h"


Player::Player(glm::vec3 position, glm::vec3 box) : m_position(position), m_box(box) {
    m_speed = glm::vec3(0.0f, 0.0f, 0.0f);
    m_gravity = glm::vec3(0.0f, -0.8f, 0.0f);
}

void Player::update() {
    m_speed.y += m_gravity.y * 0.1f;
    m_position += m_speed * 0.1f;
}

glm::vec3 Player::getPosition() const {
    return m_position;
}

void Player::setPosition(glm::vec3 position) {
    m_position = position;
}

glm::vec3 Player::getBox() const {
    return m_box;
}

AABB Player::getAABB() const {
    glm::vec3 half(m_box.x * 0.5f, 0.0f, m_box.z * 0.5f);
    glm::vec3 min = m_position - half;
    return { min, min + m_box };
}

void Player::setSpeed(glm::vec3 vec) {
    this->m_speed = vec;
}

glm::vec3 Player::getSpeed() const {
    return m_speed;
}
