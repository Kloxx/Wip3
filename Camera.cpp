#include "Camera.h"

#include <glm/gtx/transform.hpp>

Camera::Camera(float distanceX, float distanceY, const glm::vec3& verticalAxe, const glm::mat4& projectionBase) :
    m_distanceX(distanceX), m_distanceY(distanceY), m_verticalAxe(verticalAxe),
    m_replayView(false), m_position(),
    m_projectionBase(projectionBase)
{
}

glm::mat4 Camera::getCameraProjection(const Ship& ship)
{
    const glm::vec3 positionShip = ship.getPosition();
    const glm::vec3 orientationShip = ship.getOrientation();
    const glm::vec3 orientation(glm::normalize(orientationShip - positionShip));
    const glm::vec3 distance = glm::vec3(0, m_distanceY, 0) - orientation * m_distanceX;

    glm::mat4 projection = m_projectionBase;
    if (m_replayView) {
        m_position = glm::vec3(200,50,120);
        projection *= glm::lookAt(m_position, ship.getPosition(), m_verticalAxe);
    } else {
        m_position = positionShip + distance;
        projection *= glm::lookAt(m_position, ship.getOrientation(), m_verticalAxe);
    }
    return projection;
}
