#include "Track.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

float
linspace(const unsigned int kk, const unsigned int kk_max, const float min_value, const float max_value)
{
    const float xx = static_cast<float>(kk+1)/(kk_max+1);
    return min_value + (max_value-min_value)*xx;
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

template <size_t additional_vertices>
struct Profile
{
    typedef Profile<additional_vertices> Self;

    static
    Self
    flatProfile(const float& width, Track& track);

    void
    extrude(const Self& profile, Track& track) const;

protected:
    typedef Array<std::pair<glm::vec3, glm::vec2>, 7> Border;
    typedef Array<glm::vec3, 1+2*(Border::size+additional_vertices)> Vertices;
    typedef Array<glm::vec2, 1+2*(Border::size+additional_vertices)> TextureCoords;
    typedef Array<unsigned int, 1+2*(Border::size+additional_vertices)> Indexes;

    Indexes indexes;

};

template <size_t additional_vertices>
Profile<additional_vertices>
Profile<additional_vertices>::flatProfile(const float& width, Track& track)
{
    const float margin = 6;
    const float height = 3;
    const float road_thickness = 4;
    const float wall_thickness = 2;
    const float bevel = 2;
    assert( margin < width );

    Border left_border;
    left_border[0] = std::make_pair(glm::vec3(0,-road_thickness,0),                            glm::vec2(2/16.,0));
    left_border[1] = std::make_pair(glm::vec3(0,-road_thickness,-margin-wall_thickness+bevel), glm::vec2(2.5/16.,0));
    left_border[2] = std::make_pair(glm::vec3(0,bevel-road_thickness,-margin-wall_thickness),  glm::vec2(3/16.,0));
    left_border[3] = std::make_pair(glm::vec3(0,height,-margin-wall_thickness),                glm::vec2(4.5/16.,0));
    left_border[4] = std::make_pair(glm::vec3(0,height,-margin),                               glm::vec2(5/16.,0));
    left_border[5] = std::make_pair(glm::vec3(0,0,-margin),                                    glm::vec2(6/16.,0));
    left_border[6] = std::make_pair(glm::vec3(0,0,0),                                          glm::vec2(6.5/16.,0));

    Border right_border;
    for (size_t kk=0; kk<Border::size; kk++)
    {
        glm::vec3 vertex = left_border[kk].first;
        glm::vec2 texture_coord = left_border[kk].second;
        vertex.z = -vertex.z;
        texture_coord.x = 1-texture_coord.x;
        right_border[Border::size-1-kk] = std::make_pair(vertex, texture_coord);
    }

    Vertices vertices;
    TextureCoords texture_coords;

    {
        size_t kk = 0;

        // left border
        for (size_t ll=0; ll<Border::size; ll++)
        {
            vertices[kk] = glm::transform(glm::translate(glm::vec3(0,0,-width)), left_border[ll].first);
            texture_coords[kk] = left_border[ll].second;
            kk++;
        }

        // top
        for (size_t ll=0; ll<additional_vertices; ll++)
        {
            const float shift_vertex = linspace(ll, additional_vertices, -width, width);
            vertices[kk] = glm::transform(glm::translate(glm::vec3(0,0,shift_vertex)), glm::vec3(0,0,0));
            const float shift_texture_coord = linspace(ll, additional_vertices, left_border[Border::size-1].second.x, right_border[0].second.x);
            texture_coords[kk] = glm::transform(glm::translate(glm::vec2(shift_texture_coord, 0)), glm::vec2(0,0));
            kk++;
        }

        // right border
        for (size_t ll=0; ll<Border::size; ll++)
        {
            vertices[kk] = glm::transform(glm::translate(glm::vec3(0,0,width)), right_border[ll].first);
            texture_coords[kk] = right_border[ll].second;
            kk++;
        }

        // bottom
        for (size_t ll=0; ll<additional_vertices; ll++)
        {
            const float shift_vertex = linspace(ll, additional_vertices, width, -width);
            vertices[kk] = glm::transform(glm::translate(glm::vec3(0,0,shift_vertex)), glm::vec3(0,-road_thickness,0));
            const float shift_texture_coord = linspace(ll, additional_vertices, right_border[Border::size-1].second.x, 1+left_border[0].second.x);
            texture_coords[kk] = glm::transform(glm::translate(glm::vec2(shift_texture_coord, 0)), glm::vec2(0,0));
            kk++;
        }

        assert( kk == Indexes::size-1 );

        vertices[kk] = vertices[0];

        texture_coords[kk] = texture_coords[0];
        texture_coords[kk].x += 1;
    }

    Self profile;
    for (unsigned int kk=0; kk<Indexes::size; kk++)
        profile.indexes[kk] = track.appendPoint(vertices[kk], texture_coords[kk]);

    track.registerTransform();

    return profile;
}

template <size_t additional_vertices>
void
Profile<additional_vertices>::extrude(const Self& profile_next, Track& track) const
{
    for (unsigned int kk=0; kk<Indexes::size-1; kk++)
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

    transforms.clear();

    vertices.clear();
    texture_coords.clear();
    indexes.clear();
}

void
Track::build()
{
    const glm::vec4 final_position = transform_vertices * glm::vec4(0,0,0,1);
    cout << "final position " << glm::to_string(final_position.xyz()/final_position.w) << endl;
    cout << "transforms size " << transforms.size() << endl;
    assert( vertices.size() == texture_coords.size() );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof(Indexes::value_type), indexes.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int
Track::appendPoint(const glm::vec3& vertex, const glm::vec2& texture_coord)
{
    unsigned int index = vertices.size();

    vertices.push_back(glm::transform(transform_vertices, vertex));
    texture_coords.push_back(glm::transform(transform_texture_coords, texture_coord));

    return index;
}

float
Track::registerTransform()
{
    const glm::vec3 map_origin_homo = transform_texture_coords * glm::vec3(0,0,1);
    const glm::vec2 map_origin = map_origin_homo.xy()/map_origin_homo.z;
    assert( map_origin.x == 0 );
    const float length = map_origin.y;

    //cout << "prout " << glm::to_string(map_origin) << " " << length << " " << (transforms.find(length) != transforms.end() ? "found" : "not found") << endl;

    if (transforms.find(length) != transforms.end()) return length;

    transforms.insert(std::make_pair(length, transform_vertices));
    return length;
}

typedef Profile<5> TrackProfile;

void
Track::appendStraight(const float start_width, const float end_width, const float length, const unsigned int subdiv)
{
    cout << "straigth piece start_width=" << start_width << " end_width=" << end_width << " length=" << length << endl;

    TrackProfile last_profile = TrackProfile::flatProfile(start_width, *this);
    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        const float width = start_width + (end_width-start_width) * smooth_interp(kk, subdiv);
        TrackProfile next_profile = TrackProfile::flatProfile(width, *this);
        last_profile.extrude(next_profile, *this);
        last_profile = next_profile;
    }
}

void
Track::appendTurn(const float width, const float angle, const float length, const unsigned int subdiv)
{
    const float radius = length/angle;
    cout << "turn piece width=" << width << " angle=" << angle << " length=" << length << " radius=" << radius << endl;

    TrackProfile last_profile = TrackProfile::flatProfile(width, *this);
    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv/2.,0,0)) * glm::rotate(angle/subdiv, glm::vec3(0,1,0)) * glm::translate(glm::vec3(length/subdiv/2.,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        TrackProfile next_profile = TrackProfile::flatProfile(width, *this);
        last_profile.extrude(next_profile, *this);
        last_profile = next_profile;
    }
}

void
Track::appendTwist(const float width, const float angle, const float length, const unsigned int subdiv)
{
    const float radius = length/angle;
    cout << "twist piece width=" << width << " angle=" << angle << " length=" << length << " radius=" << radius << endl;

    TrackProfile last_profile = TrackProfile::flatProfile(width, *this);
    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv,0,0)) * glm::rotate(angle*smooth_diff(kk, subdiv), glm::vec3(1,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        TrackProfile next_profile = TrackProfile::flatProfile(width, *this);
        last_profile.extrude(next_profile, *this);
        last_profile = next_profile;
    }
}

void
Track::appendQuarter(const float width, const float angle, const float length, const unsigned int subdiv)
{
    const float radius = length/angle;
    cout << "quarter piece width=" << width << " angle=" << angle << " length=" << length << " radius=" << radius << endl;

    TrackProfile last_profile = TrackProfile::flatProfile(width, *this);
    for (unsigned int kk=1; kk<=subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv/2.,0,0)) * glm::rotate(angle/subdiv, glm::vec3(0,0,1)) * glm::translate(glm::vec3(length/subdiv/2.,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        unsigned int new_left_index = appendPoint(glm::vec3(0,0,-width), glm::vec2(0,0));
        unsigned int new_right_index = appendPoint(glm::vec3(0,0,width), glm::vec2(1,0));

        TrackProfile next_profile = TrackProfile::flatProfile(width, *this);
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

