#include "Cube.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Cube::Cube(const double& scale, std::string const& vertexShader, std::string const& fragmentShader) :
    m_scale(scale),
    m_shader(vertexShader, fragmentShader)
{
    // Temporary vertex
    //taille /= 2;
    float vertexTmp[] =
    {0.0,0.0,0.0,        1,0.0,0.0,        1,1,0.0,
     0.0,0.0,0.0,        0.0,1,0.0,        1,1,0.0,
     1,0.0,1,  1,0.0,0.0,        1,1,0.0,
     1,0.0,1,  1,1,         1,1,1,0.0,
     0.0,0.0,1, 1,0.0,1,     1,0.0,0.0,
     0.0,0.0,1, 0.0,0.0,0.0,           1,0.0,0.0,
     0.0,0.0,1, 1,0.0,1,     1,1,1,
     0.0,0.0,1, 0.0,1,1,     1,1,1,
     0.0,0.0,0.0,        0.0,0.0,1.5*1,    0.0,1,1,
     0.0,0.0,0.0,        0.0,1,0.0,        0.0,1,1,
     0.0,1,1,  1,1,1,  1,1,0.0,
     0.0,1,1,  0.0,1,0.0,        1,1,0.0};

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
    glm::mat4 modelview_local = glm::scale(modelview, glm::vec3(m_scale, m_scale, m_scale));

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


Box::Box(const double& scale, const std::string& vertexShader, const std::string& fragmentShader, const std::string& texture) :
    Cube(scale, vertexShader, fragmentShader), m_texture(texture)
{
    m_texture.load();
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
    glUseProgram(m_shader.getProgramID());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertex);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_colors);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
    glEnableVertexAttribArray(2);

    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
    glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindTexture(GL_TEXTURE_2D, m_texture.getID());
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}
