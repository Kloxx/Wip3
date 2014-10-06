#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

// OpenGL
#ifdef WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#endif // WIN32

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other
#include "Shader.h"
#include "Texture.h"

class Cube
{
public:
    Cube(float taille, std::string const vertexShader, std::string const fragmentShader);
    ~Cube();
    void afficher(glm::mat4 &projection, glm::mat4 &modelview);

protected:
    Shader m_shader;
    float m_vertex[108];
    float m_colors[108];
};

class Box : public Cube
{
public:
    Box(float taille, std::string const vertexShader, std::string const fragmentShader, std::string texture);
    ~Box();
    void afficher(glm::mat4 &projection, glm::mat4 &modelview);

private:
    Texture m_texture;
    float m_coordTexture[72];
};

#endif // CUBE_H_INCLUDED
