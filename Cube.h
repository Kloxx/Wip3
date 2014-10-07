#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "common.h"

// Other
#include "Shader.h"
#include "Texture.h"

class Cube
{
public:
    Cube(const Shader& shader, const double& scale);
    void draw(const glm::mat4& projection, const glm::mat4& modelview);

protected:
    double m_scale;
    Shader m_shader;
    float m_vertex[108];
    float m_colors[108];
};

class Box : public Cube
{
public:
    Box(const Shader& shader, const std::string& texture, const double& scale);
    void draw(const glm::mat4& projection, const glm::mat4& modelview);

protected:
    Texture m_texture;
    float m_coordTexture[72];
};

class Skybox : public Box
{
public:
		Skybox(const Shader& shader, const std::string& texture, const double& scale);
};

#endif // CUBE_H_INCLUDED
