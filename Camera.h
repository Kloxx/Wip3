#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Input.h"
#include "Ship.h"

class CameraDoom
{
public:
    CameraDoom();
    CameraDoom(glm::vec3 position, glm::vec3 orientation, glm::vec3 verticalAxe, float speed, float rotationSpeed);
    ~CameraDoom();
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

class CameraThirdPerson
{
public:
    CameraThirdPerson(glm::vec3 distance, glm::vec3 verticalAxe);
    ~CameraThirdPerson();
    void lookAt(glm::mat4& modelview, Ship &ship);

private:
    glm::vec3 m_distance;
    glm::vec3 m_verticalAxe;
};

#endif // CAMERA_H_INCLUDED
