//
// Created by aureliano on 27/10/26.
//

#ifndef MINI_MINECRAFT_CAMERA_H
#define MINI_MINECRAFT_CAMERA_H
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

class Camera {
private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;

    float m_speed;
public:
    Camera();

    glm::mat4 getViewMatrix();

    glm::vec3 getPosition();
    void setPosition(glm::vec3 position);
    glm::vec3 getFront();
    void setFront(glm::vec3 front);
    glm::vec3 getUp();
    void setUp(glm::vec3 up);
    float getSpeed() const;
    void setSpeed(float speed);
};


#endif //MINI_MINECRAFT_CAMERA_H
