#include "Track.h"

#include <glm/gtx/transform.hpp>
#include <iostream>

using std::cout;
using std::endl;

static
unsigned int
push_push(Vertices& vertices, TextureCoords& texture_coords, const glm::vec4& vertex, const glm::vec2& texture_coord)
{
    unsigned int index = vertices.size();
    glm::vec3 vertex_std = vertex.xyz();
    vertex_std /= vertex.w;
    vertices.push_back(vertex_std);
    texture_coords.push_back(texture_coord);
    return index;
}

void
Piece::fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const
{
}

PieceStraight::PieceStraight(const float start_width, const float end_width, const float length) :
    Piece(),
    start_width(start_width), end_width(end_width), length(length)
{
}

void
PieceStraight::fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const
{
    const unsigned int start_left_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,-start_width,1), glm::vec2(0,0));
    const unsigned int start_right_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,start_width,1), glm::vec2(1,0));
    glm::translate(transform, glm::vec3(length,0,0));
    const unsigned int end_left_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,-end_width,1), glm::vec2(0,1));
    const unsigned int end_right_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,end_width,1), glm::vec2(1,1));

    indexes.push_back(glm::uvec3(start_left_index, start_right_index, end_right_index));
    indexes.push_back(glm::uvec3(start_left_index, end_right_index, end_left_index));
}


Track::Track(const Shader& shader, const std::string& texture, const Pieces& pieces) :
    shader(shader),
    texture(texture)
{
    glm::mat4 transform(1);
    for (Pieces::const_iterator piece_iter=pieces.begin(), piece_end=pieces.end(); piece_iter!=piece_end; piece_iter++)
    {
        const Piece& piece = *piece_iter;
        piece.fillBuffers(transform, vertices, texture_coords, indexes);
    }

    cout << "track " << sizeof(indexes) << " " << indexes.size() << endl;

    glGenBuffers(1, &indexes_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size(), indexes.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void
Track::draw(const glm::mat4& modelview) const
{
    glm::mat4 modelview_local = modelview;
    //modelview_local = glm::scale(modelview_local, glm::vec3(m_scale, m_scale, m_scale));
    shader.setUniform("modelview", modelview_local);

    glUseProgram(shader.getProgramID());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices.data());
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, texture_coords.data());
    glEnableVertexAttribArray(2);

    glBindTexture(GL_TEXTURE_2D, texture.getID());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_buffer);
    glDrawElements(GL_TRIANGLES, indexes.size()*3, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(0);

    glUseProgram(0);

}

