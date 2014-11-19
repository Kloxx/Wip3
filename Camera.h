#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "common.h"

#include "Ship.h"
#include "Track.h"

class Camera
{
public:
    Camera(float distanceX, float distanceY, const glm::vec3& verticalAxe, const glm::mat4& projectionBase);
    glm::mat4 getCameraProjection(const Ship& ship, const Track& track, const float time);

    enum Type {SHIP_VIEW, REPLAY_VIEW, TRACK_VIEW};
    Type m_type;
    glm::vec3 m_position;

private:
    float m_distanceX;
    float m_distanceY;
    glm::vec3 m_verticalAxe;
    glm::mat4 m_projectionBase;
};

#endif // CAMERA_H_INCLUDED
