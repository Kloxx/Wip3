#include "Cube.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube(const Shader& shader, const double& scale) :
    m_scale(scale),
    m_shader(shader)
{
    // Temporary vertex
    //taille /= 2;
    float vertexTmp[] =
    {-1,-1,-1,        1,-1,-1,        1,1,-1,
     -1,-1,-1,        -1,1,-1,        1,1,-1,
     1,-1,1,  1,-1,-1,        1,1,-1,
     1,-1,1,  1,1,         1,1,1,-1,
     -1,-1,1, 1,-1,1,     1,-1,-1,
     -1,-1,1, -1,-1,-1,           1,-1,-1,
     -1,-1,1, 1,-1,1,     1,1,1,
     -1,-1,1, -1,1,1,     1,1,1,
     -1,-1,-1,        -1,-1,1,    -1,1,1,
     -1,-1,-1,        -1,1,-1,        -1,1,1,
     -1,1,1,  1,1,1,  1,1,-1,
     -1,1,1,  -1,1,-1,        1,1,-1};

    float colorsTmp[] =
    {1.0,0.0,0.0, 1.0,0.0,0.0, 1.0,0.0,0.0,
     1.0,0.0,0.0, 1.0,0.0,0.0, 1.0,0.0,0.0,
     0.0,1.0,0.0, 0.0,1.0,0.0, 0.0,1.0,0.0,
     0.0,1.0,0.0, 0.0,1.0,0.0, 0.0,1.0,0.0,
     0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0,
     0.0,0.0,1.0, 0.0,0.0,1.0, 0.0,0.0,1.0,
     1.0,1.0,0.0, 1.0,1.0,0.0, 1.0,1.0,0.0,
     1.0,1.0,0.0, 1.0,1.0,0.0, 1.0,1.0,0.0,
     1.0,0.0,1.0, 1.0,0.0,1.0, 1.0,0.0,1.0,
     1.0,0.0,1.0, 1.0,0.0,1.0, 1.0,0.0,1.0,
     0.0,1.0,1.0, 0.0,1.0,1.0, 0.0,1.0,1.0,
     0.0,1.0,1.0, 0.0,1.0,1.0, 0.0,1.0,1.0};

     for(int i(0); i<108; i++)
     {
         m_vertex[i] = vertexTmp[i];
         m_colors[i] = colorsTmp[i];
     }
}

void
Cube::draw(const glm::mat4 &projection, const glm::mat4 &modelview)
{
    glm::mat4 modelview_local = modelview;
    modelview_local = glm::scale(modelview_local, glm::vec3(m_scale, m_scale, m_scale));

    glUseProgram(m_shader.getProgramID());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertex);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_colors);
    glEnableVertexAttribArray(1);

    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview_local));
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}


Box::Box(const Shader& shader, const std::string& texture, const double& scale) :
    Cube(shader, scale),
    m_texture(texture)
{
    float coordTextureTmp[] = {
        0,0, 1,0, 1,1,
        0,0, 0,1, 1,1,
        0,0, 1,0, 1,1,
        0,0, 0,1, 1,1,
        0,0, 1,0, 1,1,
        0,0, 0,1, 1,1,
        0,0, 1,0, 1,1,
        0,0, 0,1, 1,1,
        0,0, 1,0, 1,1,
        0,0, 0,1, 1,1,
        0,0, 1,0, 1,1,
        0,0, 0,1, 1,1
    };
    for(int i(0); i<72; i++)
        m_coordTexture[i] = coordTextureTmp[i];
}

void
Box::draw(const glm::mat4& projection, const glm::mat4& modelview)
{
    glm::mat4 modelview_local = modelview;
    modelview_local = glm::scale(modelview_local, glm::vec3(m_scale, m_scale, m_scale));

    glUseProgram(m_shader.getProgramID());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertex);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_colors);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
    glEnableVertexAttribArray(2);

    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview_local));
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindTexture(GL_TEXTURE_2D, m_texture.getID());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}

Skybox::Skybox(const Shader& shader, const std::string& texture, const double& scale) :
    Box(shader, texture, scale)
{
    float coordTextureTmp[] = {
        0/4.,1/3., 1/4.,1/3., 1/4.,2/3., //left
        0/4.,1/3., 0/4.,2/3., 1/4.,2/3.,
        2/4.,1/3., 1/4.,1/3., 1/4.,2/3., //front
        2/4.,1/3., 2/4.,2/3., 1/4.,2/3.,
        2/4.,0/3., 2/4.,1/3., 1/4.,1/3., //bottom
        2/4.,0/3., 1/4.,0/3., 1/4.,1/3.,
        3/4.,1/3., 2/4.,1/3., 2/4.,2/3., //right
        3/4.,1/3., 3/4.,2/3., 2/4.,2/3.,
        4/4.,1/3., 3/4.,1/3., 3/4.,2/3., //back
        4/4.,1/3., 4/4.,2/3., 3/4.,2/3.,
        2/4.,3/3., 2/4.,2/3., 1/4.,2/3., //top
        2/4.,3/3., 1/4.,3/3., 1/4.,2/3.,
    };
    for(int i(0); i<72; i++)
        m_coordTexture[i] = coordTextureTmp[i];
}
