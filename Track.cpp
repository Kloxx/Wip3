#include "Track.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>


glm::mat3
translate2(const glm::vec2& vec)
{
    glm::mat3 mat_trans(1);
    mat_trans[2][0] = vec[0];
    mat_trans[2][1] = vec[1];
    return mat_trans;
}

float
smooth_function(const float xx)
{
    if (xx<0) return 0;
    if (xx>1) return 1;
    return xx*xx*(3-2*xx);
}

float
smooth_interp(const unsigned int kk, const unsigned int kk_max)
{
    const float xx = static_cast<float>(kk)/(kk_max-1);
    return smooth_function(xx);
}

float
smooth_diff(const unsigned int kk, const unsigned int kk_max)
{
    const float xx_current = static_cast<float>(kk)/kk_max;
    const float xx_next = static_cast<float>(kk+1)/kk_max;
    return smooth_function(xx_next)-smooth_function(xx_current);
}

using std::cout;
using std::endl;

Track::Profile::Profile(const float& width, Track& track)
{
    const float margin = 6;
    const float height = 3;
    const float road_thickness = 4;
    const float wall_thickness = 2;
    const float bevel = 2;
    assert( margin < width );

    glm::vec3 vertices[14];
    vertices[0]  = glm::vec3(0,0,0);
    vertices[1]  = glm::vec3(0,0,width-margin);
    vertices[2]  = glm::vec3(0,0,width);
    vertices[3]  = glm::vec3(0,height,width);
    vertices[4]  = glm::vec3(0,height,width+wall_thickness);
    vertices[5]  = glm::vec3(0,bevel-road_thickness,width+wall_thickness);
    vertices[6]  = glm::vec3(0,-road_thickness,width+wall_thickness-bevel);
    vertices[7]  = glm::vec3(0,-road_thickness,-width-wall_thickness+bevel);
    vertices[8]  = glm::vec3(0,bevel-road_thickness,-width-wall_thickness);
    vertices[9]  = glm::vec3(0,height,-width-wall_thickness);
    vertices[10] = glm::vec3(0,height,-width);
    vertices[11] = glm::vec3(0,0,-width);
    vertices[12] = glm::vec3(0,0,-width+margin);
    vertices[13] = glm::vec3(0,0,0);

    glm::vec2 texture_coords[14];
    texture_coords[0]  = glm::vec2(8/16.,0);
    texture_coords[1]  = glm::vec2(9.5/16.,0);
    texture_coords[2]  = glm::vec2(10/16.,0);
    texture_coords[3]  = glm::vec2(11/16.,0);
    texture_coords[4]  = glm::vec2(11.5/16.,0);
    texture_coords[5]  = glm::vec2(13/16.,0);
    texture_coords[6]  = glm::vec2(13.5/16.,0);
    texture_coords[7]  = glm::vec2(1.+2.5/16.,0);
    texture_coords[8]  = glm::vec2(1.+3/16.,0);
    texture_coords[9]  = glm::vec2(1.+4.5/16.,0);
    texture_coords[10] = glm::vec2(1.+5/16.,0);
    texture_coords[11] = glm::vec2(1.+6/16.,0);
    texture_coords[12] = glm::vec2(1.+6.5/16.,0);
    texture_coords[13] = glm::vec2(1.+8/16.,0);

    for (unsigned int kk=0; kk<14; kk++)
        indexes[kk] = track.appendPoint(vertices[kk], texture_coords[kk]);
}

void
Track::Profile::extrude(const Profile& profile_next, Track& track) const
{
    for (unsigned int kk=0; kk<13; kk++)
    {
        track.indexes.push_back(glm::uvec3(indexes[kk], indexes[kk+1], profile_next.indexes[kk+1]));
        track.indexes.push_back(glm::uvec3(indexes[kk], profile_next.indexes[kk+1], profile_next.indexes[kk]));
    }
}

Track::Track(const Shader& shader, const std::string& texture) :
    shader(shader),
    texture(texture)
{
    glGenBuffers(1, &indexes_buffer);
    assert( indexes_buffer );
    clear();
}

void
Track::clear()
{
    transform_vertices = glm::mat4(1);
    transform_texture_coords = glm::mat3(1);

    vertices.clear();
    texture_coords.clear();
    indexes.clear();
}

void
Track::build()
{
    const glm::vec4 final_position = transform_vertices * glm::vec4(0,0,0,1);
    cout << "final position " << glm::to_string(final_position.xyz()/final_position.w) << endl;
    assert( vertices.size() == texture_coords.size() );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof(Indexes::value_type), indexes.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int
Track::appendPoint(const glm::vec3& vertex, const glm::vec2& texture_coord)
{
    unsigned int index = vertices.size();

    { // transform vertex
        const glm::vec4 vertex_homo(vertex, 1);
        const glm::vec4 vertex_transform_homo = transform_vertices * vertex_homo;
        glm::vec3 vertex_transform = vertex_transform_homo.xyz();
        vertex_transform /= vertex_transform_homo.w;
        vertices.push_back(vertex_transform);
    }

    { // trasnform texture coord
        const glm::vec3 texture_coord_homo(texture_coord, 1);
        const glm::vec3 texture_coord_transform_homo = transform_texture_coords * texture_coord_homo;
        glm::vec2 texture_coord_transform = texture_coord_transform_homo.xy();
        texture_coord_transform /= texture_coord_transform_homo.z;
        texture_coords.push_back(texture_coord_transform);
    }

    return index;
}

void
Track::appendStraight(const float start_width, const float end_width, const float length, const unsigned int subdiv)
{
    cout << "straigth piece start_width=" << start_width << " end_width=" << end_width << " length=" << length << endl;

    Profile last_profile(start_width, *this);
    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv,0,0));
        transform_texture_coords *= translate2(glm::vec2(0,length/subdiv/32.));

        const float width = start_width + (end_width-start_width) * smooth_interp(kk, subdiv);
        Profile next_profile(width, *this);
        last_profile.extrude(next_profile, *this);
        last_profile = next_profile;
    }
}

void
Track::appendTurn(const float width, const float angle, const float length, const unsigned int subdiv)
{
    const float radius = length/angle;
    cout << "turn piece width=" << width << " angle=" << angle << " length=" << length << " radius=" << radius << endl;

    Profile last_profile(width, *this);
    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv/2.,0,0)) * glm::rotate(angle/subdiv, glm::vec3(0,1,0)) * glm::translate(glm::vec3(length/subdiv/2.,0,0));
        transform_texture_coords *= translate2(glm::vec2(0,length/subdiv/32.));

        Profile next_profile(width, *this);
        last_profile.extrude(next_profile, *this);
        last_profile = next_profile;
    }
}

void
Track::appendTwist(const float width, const float angle, const float length, const unsigned int subdiv)
{
    const float radius = length/angle;
    cout << "twist piece width=" << width << " angle=" << angle << " length=" << length << " radius=" << radius << endl;

    Profile last_profile(width, *this);
    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv,0,0)) * glm::rotate(angle*smooth_diff(kk, subdiv), glm::vec3(1,0,0));
        transform_texture_coords *= translate2(glm::vec2(0,length/subdiv/32.));

        Profile next_profile(width, *this);
        last_profile.extrude(next_profile, *this);
        last_profile = next_profile;
    }
}

void
Track::appendQuarter(const float width, const float angle, const float length, const unsigned int subdiv)
{
    const float radius = length/angle;
    cout << "quarter piece width=" << width << " angle=" << angle << " length=" << length << " radius=" << radius << endl;

    Profile last_profile(width, *this);
    for (unsigned int kk=1; kk<=subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv/2.,0,0)) * glm::rotate(angle/subdiv, glm::vec3(0,0,1)) * glm::translate(glm::vec3(length/subdiv/2.,0,0));
        transform_texture_coords *= translate2(glm::vec2(0,length/subdiv/32.));

        unsigned int new_left_index = appendPoint(glm::vec3(0,0,-width), glm::vec2(0,0));
        unsigned int new_right_index = appendPoint(glm::vec3(0,0,width), glm::vec2(1,0));

        Profile next_profile(width, *this);
        last_profile.extrude(next_profile, *this);
        last_profile = next_profile;
    }
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

