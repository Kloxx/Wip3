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

    if (m_type == REPLAY_VIEW)
    {
        const glm::mat4 ship_transform = ship.getTransform();
        m_position = glm::vec3(200,50,120);
        return m_projectionBase * glm::lookAt(m_position, glm::transform(ship_transform, glm::vec3(0,0,0)), m_verticalAxe);
    }

    if (m_type == TRACK_VIEW)
    {
        const glm::vec3 origin = track.getPosition(glm::vec2(.2*cos(5*time), 3*time), 5);
        const glm::vec3 to = track.getPosition(glm::vec2(.2*cos(5*time+1), 3*time+1), 5);
        const glm::vec3 up = track.getPosition(glm::vec2(.2*cos(5*time), 3*time), 6) - origin;
        m_position = origin;
        return m_projectionBase * glm::lookAt(m_position, to, up);
    }

    if (m_type == SHIP_VIEW)
    {
        const glm::mat4 ship_transform = ship.getTransform();
        const glm::vec3 ship_position = glm::transform(ship_transform, glm::vec3(0,0,0));
        const glm::vec3 ship_front = glm::transform(ship_transform, glm::vec3(m_distanceX,0,0));
        const glm::vec3 ship_up = glm::transform(ship_transform, glm::vec3(0,1,0)) - ship_position;
        m_position = glm::transform(ship_transform, glm::vec3(-m_distanceX,m_distanceY,0));
        return m_projectionBase * glm::lookAt(m_position, ship_front, ship_up);
    }

    return m_projectionBase;
}
