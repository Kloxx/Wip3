#include "Camera.h"

#include <glm/gtx/transform.hpp>

Camera::Camera(float distanceX, float distanceY, const glm::vec3& verticalAxe, const glm::mat4& projectionBase) :
    m_distanceX(distanceX), m_distanceY(distanceY), m_verticalAxe(verticalAxe),
    m_type(SHIP_VIEW), m_position(),
    m_projectionBase(projectionBase)
{
}

glm::mat4 Camera::getCameraProjection(const Ship& ship, const Track& track, const float time)
{
    const glm::vec3 positionShip = ship.getPosition();
    const glm::vec3 orientationShip = ship.getOrientation();
    const glm::vec3 orientation(glm::normalize(orientationShip - positionShip));
    const glm::vec3 distance = glm::vec3(0, m_distanceY, 0) - orientation * m_distanceX;

    glm::mat4 projection = m_projectionBase;
    const glm::vec3 prout = track.getPosition(glm::vec2(.2*cos(5*time), 3*time), 5);
    const glm::vec3 up = track.getPosition(glm::vec2(.2*cos(5*time), 3*time), 6) - prout;
    const glm::vec3 to = track.getPosition(glm::vec2(.2*cos(5*time+1), 3*time+1), 5);
    switch (m_type)
    {
        case REPLAY_VIEW:
            m_position = glm::vec3(200,50,120);
            projection *= glm::lookAt(m_position, ship.getPosition(), m_verticalAxe);
            break;
        case TRACK_VIEW:
            m_position = prout;
            projection *= glm::lookAt(m_position, to, up);
            break;
        case SHIP_VIEW:
            m_position = positionShip + distance;
            projection *= glm::lookAt(m_position, ship.getOrientation(), m_verticalAxe);
            break;
    }

    return projection;
}
