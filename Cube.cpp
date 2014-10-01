#include "Cube.h"

using namespace glm;

Cube::Cube(float taille, std::string const vertexShader, std::string const fragmentShader) : m_shader(vertexShader, fragmentShader)
{
    m_shader.charger();

    // Temporary vertex
    //taille /= 2;
    float vertexTmp[] =
    {0.0,0.0,0.0,        taille,0.0,0.0,        taille,taille,0.0,
     0.0,0.0,0.0,        0.0,taille,0.0,        taille,taille,0.0,
     taille,0.0,taille,  taille,0.0,0.0,        taille,taille,0.0,
     taille,0.0,taille,  taille,taille,         taille,taille,taille,0.0,
     0.0,0.0,1.5*taille, taille,0.0,taille,     taille,0.0,0.0,
     0.0,0.0,1.5*taille, 0.0,0.0,0.0,           taille,0.0,0.0,
     0.0,0.0,1.5*taille, taille,0.0,taille,     taille,taille,taille,
     0.0,0.0,1.5*taille, 0.0,taille,taille,     taille,taille,taille,
     0.0,0.0,0.0,        0.0,0.0,1.5*taille,    0.0,taille,taille,
     0.0,0.0,0.0,        0.0,taille,0.0,        0.0,taille,taille,
     0.0,taille,taille,  taille,taille,taille,  taille,taille,0.0,
     0.0,taille,taille,  0.0,taille,0.0,        taille,taille,0.0};

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

Cube::~Cube(){}

void Cube::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    glUseProgram(m_shader.getProgramID());

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertex);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_colors);
        glEnableVertexAttribArray(1);

        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

    glUseProgram(0);
}


Box::Box(float taille, std::string const vertexShader, std::string const fragmentShader, std::string const texture) : Cube(taille, vertexShader, fragmentShader), m_texture(texture)
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

Box::~Box(){}

void Box::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    glUseProgram(m_shader.getProgramID());

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertex);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_coordTexture);
        glEnableVertexAttribArray(2);

        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));

        glBindTexture(GL_TEXTURE_2D, m_texture.getID());
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindTexture(GL_TEXTURE_2D, 0);

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

    glUseProgram(0);
}
