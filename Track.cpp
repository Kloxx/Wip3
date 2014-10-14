#include "Track.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

using std::cout;
using std::endl;

static
unsigned int
push_push(Vertices& vertices, TextureCoords& texture_coords, const glm::vec4& vertex, const glm::vec3& texture_coord)
{
    unsigned int index = vertices.size();

    glm::vec3 vertex_std = vertex.xyz();
    vertex_std /= vertex.w;
    vertices.push_back(vertex_std);

    glm::vec2 texture_coord_std = texture_coord.xy();
    texture_coord_std /= texture_coord.z;
    texture_coords.push_back(texture_coord_std);

    return index;
}

glm::mat3
translate2(const glm::vec2& vec)
{
    glm::mat3 mat_trans(1);
    mat_trans[2][0] = vec[0];
    mat_trans[2][1] = vec[1];
    return mat_trans;
}

float
smooth_inter(const float xx)
{
    if (xx<0) return 0;
    if (xx>1) return 1;
    return 3*xx*xx-2*xx*xx*xx;
}

PieceStraight::PieceStraight(const float start_width, const float end_width, const float length) :
    Piece(),
    start_width(start_width), end_width(end_width), length(length)
{
}

void
PieceStraight::fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const
{
    cout << "straigth piece start_width=" << start_width << " end_width=" << end_width << " length=" << length << endl;

    const unsigned int start_left_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,-start_width,1), glm::vec3(0,0,1));
    const unsigned int start_right_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,start_width,1), glm::vec3(1,0,1));
    transform *= glm::translate(glm::vec3(length,0,0));
    const unsigned int end_left_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,-end_width,1), glm::vec3(0,1,1));
    const unsigned int end_right_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,end_width,1), glm::vec3(1,1,1));

    indexes.push_back(glm::uvec3(start_left_index, start_right_index, end_right_index));
    indexes.push_back(glm::uvec3(start_left_index, end_right_index, end_left_index));
}

PieceTurn::PieceTurn(const float width, const float angle, const float length, const unsigned int subdiv) :
    Piece(),
    width(width), angle(angle), length(length), subdiv(subdiv)
{
}

void
PieceTurn::fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const
{
    const float radius = length/angle;
    cout << "turn piece width=" << width << " angle=" << angle << " length=" << length << " radius=" << radius << endl;

    glm::mat3 transform_texture_coords(1);
    unsigned int last_left_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,-width,1), transform_texture_coords * glm::vec3(0,0,1));
    unsigned int last_right_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,width,1), transform_texture_coords * glm::vec3(1,0,1));
    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform *= glm::translate(glm::vec3(length/subdiv/2.,0,0)) * glm::rotate(angle/subdiv, glm::vec3(0,1,0)) * glm::translate(glm::vec3(length/subdiv/2.,0,0));
        transform_texture_coords *= translate2(glm::vec2(0,1./subdiv));

        unsigned int new_left_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,-width,1), transform_texture_coords * glm::vec3(0,0,1));
        unsigned int new_right_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,width,1), transform_texture_coords * glm::vec3(1,0,1));

        indexes.push_back(glm::uvec3(last_left_index, last_right_index, new_right_index));
        indexes.push_back(glm::uvec3(last_left_index, new_right_index, new_left_index));

        last_left_index = new_left_index;
        last_right_index = new_right_index;
    }
}

PieceTwist::PieceTwist(const float width, const float angle, const float length, const unsigned int subdiv) :
    Piece(),
    width(width), angle(angle), length(length), subdiv(subdiv)
{
}

void
PieceTwist::fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const
{
    const float radius = length/angle;
    cout << "twist piece width=" << width << " angle=" << angle << " length=" << length << " radius=" << radius << endl;

    glm::mat3 transform_texture_coords(1);
    unsigned int last_left_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,-width,1), transform_texture_coords * glm::vec3(0,0,1));
    unsigned int last_middle_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,0,1), transform_texture_coords * glm::vec3(.5,0,1));
    unsigned int last_right_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,width,1), transform_texture_coords * glm::vec3(1,0,1));
    for (unsigned int kk=1; kk<=subdiv; kk++)
    {
        const glm::mat4 transform_local = transform * glm::translate(glm::vec3(kk*length/subdiv,0,0)) * glm::rotate(angle*smooth_inter(static_cast<float>(kk)/subdiv), glm::vec3(1,0,0));
        transform_texture_coords *= translate2(glm::vec2(0,1./subdiv));

        unsigned int new_left_index = push_push(vertices, texture_coords, transform_local * glm::vec4(0,0,-width,1), transform_texture_coords * glm::vec3(0,0,1));
        unsigned int new_middle_index = push_push(vertices, texture_coords, transform_local * glm::vec4(0,0,0,1), transform_texture_coords * glm::vec3(.5,0,1));
        unsigned int new_right_index = push_push(vertices, texture_coords, transform_local * glm::vec4(0,0,width,1), transform_texture_coords * glm::vec3(1,0,1));

        indexes.push_back(glm::uvec3(last_left_index, last_middle_index, new_middle_index));
        indexes.push_back(glm::uvec3(last_middle_index, last_right_index, new_right_index));
        indexes.push_back(glm::uvec3(last_left_index, new_middle_index, new_left_index));
        indexes.push_back(glm::uvec3(last_middle_index, new_right_index, new_middle_index));

        last_left_index = new_left_index;
        last_middle_index = new_middle_index;
        last_right_index = new_right_index;
    }

    transform *= glm::translate(glm::vec3(length,0,0)) * glm::rotate(angle, glm::vec3(1,0,0));
}

PieceQuarter::PieceQuarter(const float width, const float angle, const float length, const unsigned int subdiv) :
    Piece(),
    width(width), angle(angle), length(length), subdiv(subdiv)
{
}

void
PieceQuarter::fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const
{
    const float radius = length/angle;
    cout << "quarter piece width=" << width << " angle=" << angle << " length=" << length << " radius=" << radius << endl;

    glm::mat3 transform_texture_coords(1);
    unsigned int last_left_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,-width,1), transform_texture_coords * glm::vec3(0,0,1));
    unsigned int last_right_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,width,1), transform_texture_coords * glm::vec3(1,0,1));
    for (unsigned int kk=1; kk<=subdiv; kk++)
    {
        transform *= glm::translate(glm::vec3(length/subdiv/2.,0,0)) * glm::rotate(angle/subdiv, glm::vec3(0,0,1)) * glm::translate(glm::vec3(length/subdiv/2.,0,0));
        transform_texture_coords *= translate2(glm::vec2(0,1./subdiv));

        unsigned int new_left_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,-width,1), transform_texture_coords * glm::vec3(0,0,1));
        unsigned int new_right_index = push_push(vertices, texture_coords, transform * glm::vec4(0,0,width,1), transform_texture_coords * glm::vec3(1,0,1));

        indexes.push_back(glm::uvec3(last_left_index, last_right_index, new_right_index));
        indexes.push_back(glm::uvec3(last_left_index, new_right_index, new_left_index));

        last_left_index = new_left_index;
        last_right_index = new_right_index;
    }
}

Track::Track(const Shader& shader, const std::string& texture, Pieces& pieces) :
    shader(shader),
    texture(texture)
{
    cout << "creating track with " << pieces.size() << " pieces" << endl;

    glm::mat4 transform(1);
    for (Pieces::const_iterator piece_iter=pieces.begin(), piece_end=pieces.end(); piece_iter!=piece_end; piece_iter++)
    {
        const Piece* piece = *piece_iter;
        piece->fillBuffers(transform, vertices, texture_coords, indexes);
        delete piece;
    }
    pieces.clear();

    cout << "** " << vertices.size() << " " << texture_coords.size() << " " << indexes.size() << endl;
    assert( vertices.size() == texture_coords.size() );

    for (size_t kk=0; kk<vertices.size(); kk++)
    {
        cout << glm::to_string(vertices[kk]) << " " << glm::to_string(texture_coords[kk]) << endl;
    }

    glGenBuffers(1, &indexes_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof(Indexes::value_type), indexes.data(), GL_STATIC_DRAW);
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

