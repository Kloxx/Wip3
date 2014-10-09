#include "Camera.h"

#include <glm/gtx/transform.hpp>

/*
CameraDoom::CameraDoom() :
    m_position(0,1,0), m_orientation(1,0,0), m_verticalAxe(0,1,0), m_lateralAxe(0,0,1),
    m_speed(0.5), m_rotationSpeed(0.5), m_phi(0.0)
{
}

CameraDoom::CameraDoom(glm::vec3 position, glm::vec3 orientation, glm::vec3 verticalAxe, float speed, float rotationSpeed) :
    m_position(position), m_orientation(orientation), m_verticalAxe(verticalAxe),
    m_speed(speed), m_rotationSpeed(rotationSpeed), m_phi(0.0)
{
    m_targetPoint = m_position + m_orientation;
    m_lateralAxe = glm::normalize(glm::cross(m_verticalAxe, m_orientation));
}

void CameraDoom::orientate(int direction)
{
    m_phi += direction * m_rotationSpeed;
    if(m_phi > 360.0)
        m_phi -= 360.0;
    if(m_phi < 0.0)
        m_phi += 360.0;

    float phiRad = m_phi * M_PI / 180.0;

    if(m_verticalAxe.x)
    {
        m_orientation.x = 0;
        m_orientation.y = cos(phiRad);
        m_orientation.z = sin(phiRad);
    }
    else if(m_verticalAxe.y)
    {
        m_orientation.x = cos(phiRad);
        m_orientation.y = 0;
        m_orientation.z = sin(phiRad);
    }
    else
    {
        m_orientation.x = cos(phiRad);
        m_orientation.y = sin(phiRad);
        m_orientation.z = 0;
    }

    m_lateralAxe = glm::normalize(glm::cross(m_verticalAxe, m_orientation));
    m_targetPoint = m_position + m_orientation;
}

void CameraDoom::movement(Input const& input)
{
    if(input.getKey(SDL_SCANCODE_UP) || input.getKey(SDL_SCANCODE_W))
    {
        m_position += m_orientation * m_speed;
        m_targetPoint = m_position + m_orientation;
    }
    if(input.getKey(SDL_SCANCODE_DOWN) || input.getKey(SDL_SCANCODE_S))
    {
        m_position -= m_orientation * m_speed;
        m_targetPoint = m_position + m_orientation;
    }
    if(input.getKey(SDL_SCANCODE_LEFT) || input.getKey(SDL_SCANCODE_A))
    {
        orientate(-1);
        m_targetPoint = m_position + m_orientation;
    }
    if(input.getKey(SDL_SCANCODE_RIGHT) || input.getKey(SDL_SCANCODE_D))
    {
        orientate(1);
        m_targetPoint = m_position + m_orientation;
    }
    if(input.getKey(SDL_SCANCODE_Q))
    {
        m_position += m_lateralAxe * m_speed;
        m_targetPoint = m_position + m_orientation;
    }
    if(input.getKey(SDL_SCANCODE_E))
    {
        m_position -= m_lateralAxe * m_speed;
        m_targetPoint = m_position + m_orientation;
    }
}

void CameraDoom::lookAt(glm::mat4 &modelview)
{
    modelview = glm::lookAt(m_position, m_targetPoint, m_verticalAxe);
}
*/

CameraThirdPerson::CameraThirdPerson(float distanceX, float distanceY, const glm::vec3& verticalAxe) :
    m_distanceX(distanceX), m_distanceY(distanceY), m_verticalAxe(verticalAxe), m_replayView(false)
{
}

glm::mat4 CameraThirdPerson::getCameraProjection(const glm::mat4& projection, const Ship& ship) const
{
    const glm::vec3 positionShip = ship.getPosition();
    const glm::vec3 orientationShip = ship.getOrientation();
    const glm::vec3 orientation(glm::normalize(orientationShip - positionShip));
    const glm::vec3 distance = glm::vec3(0, m_distanceY, 0) - orientation * m_distanceX;

    glm::mat4 projection_camera = projection;
    if (m_replayView) projection_camera *= glm::lookAt(glm::vec3(200, 50, 50), ship.getPosition(), m_verticalAxe);
    else projection_camera *= glm::lookAt(positionShip + distance, ship.getOrientation(), m_verticalAxe);
    return projection_camera;
}
