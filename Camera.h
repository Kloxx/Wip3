#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "common.h"

#include "Ship.h"

/*
#include "Input.h"
class CameraDoom
{
public:
    CameraDoom();
    CameraDoom(glm::vec3 position, glm::vec3 orientation, glm::vec3 verticalAxe, float speed, float rotationSpeed);
    void movement(Input const& input);
    void lookAt(glm::mat4 &modelview);

private:
    void orientate(int direction);
    glm::vec3 m_position;
    glm::vec3 m_orientation;
    glm::vec3 m_verticalAxe;
    glm::vec3 m_lateralAxe;
    glm::vec3 m_targetPoint;
    float m_speed;
    float m_rotationSpeed;
    float m_phi;
};
*/

class CameraThirdPerson
{
public:
    CameraThirdPerson(float distanceX, float distanceY, const glm::vec3& verticalAxe);
    glm::mat4 getCameraProjection(const glm::mat4& projection, const Ship& ship) const;

private:
    float m_distanceX;
    float m_distanceY;
    glm::vec3 m_verticalAxe;
};

#endif // CAMERA_H_INCLUDED
