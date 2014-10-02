#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

// OpenGL
#ifdef WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif // WIN32

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other
#include "Shader.h"
#include "Texture.h"
#include "Input.h"

class Ship
{
public:
    Ship(std::string const vertexShader, std::string const fragmentShader, std::string texture, float acceleration, float rotationSpeed);
    ~Ship();
    void draw(glm::mat4& projection, glm::mat4& modelview);
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
    float m_mass;
    glm::vec3 m_linearSpeed;
    float m_rotationSpeed;
    glm::vec3 m_position;
    glm::vec3 m_orientation;
    //void movement();
};

#endif // SHIP_H_INCLUDED
