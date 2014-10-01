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

class Ship
{
public:
    Ship(std::string const vertexShader, std::string const fragmentShader, std::string texture);
    ~Ship();
    void afficher(glm::mat4 &projection, glm::mat4 &modelview);

private:
    Shader m_shader;
    float m_vertex[720];
    float m_coordTexture[480];
    float m_normals[720];
    Texture m_texture;
};

#endif // SHIP_H_INCLUDED
