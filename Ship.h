#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "common.h"

// Other
#include "Shader.h"
#include "Texture.h"
#include "Input.h"
#include "Track.h"

class Ship
{
public:
    Ship(const Shader& shader, const std::string& texture, const Track& track);
    void draw(const glm::mat4& modelview);
    void control(Input const& input);
    glm::mat4 getTransform() const;
    //glm::vec2 getPosition() const;
    glm::vec2 getForwardDirection() const;

private:
    float m_vertex[720];
    float m_coordTexture[480];
    float m_normals[720];

    Shader m_shader;
    Texture m_texture;

    const Track& m_track;

    glm::vec2 m_position;
    glm::vec2 m_linearSpeed;
    float m_angle; // expressed in degrees
    float m_rotationSpeed;
    float m_roll; // expressed in degrees
};

#endif // SHIP_H_INCLUDED
