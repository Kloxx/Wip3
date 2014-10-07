#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "common.h"

// Other
#include "Shader.h"
#include "Texture.h"

class Cube
{
public:
    Cube(const double& scale, std::string const& vertexShader, std::string const& fragmentShader);
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
    Box(const double& scale, const std::string& vertexShader, const std::string& fragmentShader, const std::string& texture);
    void draw(const glm::mat4& projection, const glm::mat4& modelview);

protected:
    Texture m_texture;
    float m_coordTexture[72];
};

#endif // CUBE_H_INCLUDED
