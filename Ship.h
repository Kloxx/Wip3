#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "common.h"

// Other
#include "Shader.h"
#include "Texture.h"
#include "Input.h"

class Ship
{
public:
    Ship(const Shader& shader, const std::string& texture, const glm::vec3& position, float acceleration, float rotationSpeed, float mass);
    void draw(const glm::mat4& modelview);
    void control(Input const& input);
    glm::vec3 getPosition() const;
    glm::vec3 getOrientation() const;
    glm::vec3 getLinearSpeed() const;

private:
    Shader m_shader;
    float m_vertex[720];
    float m_coordTexture[480];
    float m_normals[720];
    Texture m_texture;
    float m_acceleration;
    float m_angle; // expressed in degrees
    float m_roll; // expressed in degrees
    glm::vec3 m_linearSpeed;
    float m_mass;
    float m_rotationSpeed;
    glm::vec3 m_position;
    glm::vec3 m_orientation;
    glm::vec3 movement(float acceleration) const;
    void orientate();
};

#endif // SHIP_H_INCLUDED
