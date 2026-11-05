//
// Created by aureliano on 5/11/26.
//

#include "Player.h"


Player::Player(glm::vec3 position, glm::vec3 box) : m_position(position), m_box(box) {
    m_speed = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Player::update() {
    this->m_position += this->m_speed * 0.1f;
}

glm::vec3 Player::getPosition() const {
    return m_position;
}

glm::vec3 Player::getBox() const {
    return m_box;
}

void Player::setSpeed(glm::vec3 vec) {
    this->m_speed = vec;
}

glm::vec3 Player::getSpeed() const {
    return m_speed;
}
