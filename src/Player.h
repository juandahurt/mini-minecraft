//
// Created by aureliano on 5/11/26.
//

#ifndef MINI_MINECRAFT_PLAYER_H
#define MINI_MINECRAFT_PLAYER_H
#include <glm/vec3.hpp>


class Player {
    glm::vec3 m_position;
    glm::vec3 m_box;
    glm::vec3 m_speed;
public:
    Player(glm::vec3 position, glm::vec3 box);

    void update();
    glm::vec3 getPosition() const;
    glm::vec3 getBox() const;

    void setSpeed(glm::vec3 vec);

    glm::vec3 getSpeed() const;
};


#endif //MINI_MINECRAFT_PLAYER_H
