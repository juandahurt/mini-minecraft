//
// Created by aureliano on 5/11/26.
//

#ifndef MINI_MINECRAFT_PLAYER_H
#define MINI_MINECRAFT_PLAYER_H
#include <glm/vec3.hpp>


struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

class Player {
    glm::vec3 m_position;
    glm::vec3 m_box;
    glm::vec3 m_speed;
    glm::vec3 m_gravity;
    glm::vec3 m_front;
    glm::vec3 m_up;
public:
    Player(glm::vec3 position, glm::vec3 box);

    void update();
    glm::vec3 getPosition() const;
    void setPosition(glm::vec3 position);
    glm::vec3 getBox() const;
    AABB getAABB() const;

    void setSpeed(glm::vec3 vec);

    glm::vec3 getSpeed() const;
};


#endif //MINI_MINECRAFT_PLAYER_H
