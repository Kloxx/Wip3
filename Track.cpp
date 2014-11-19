#include "Track.h"

#include <iostream>

using std::cout;
using std::endl;

Track::Track(const Shader& shader_track, const Shader& shader_map, const std::string& texture) :
    shader_track(shader_track),
    shader_map(shader_map),
    texture(texture),
    last_profile(TrackProfile::flatProfile(20))
{
    glGenBuffers(1, &indexes_buffer);
    assert( indexes_buffer );
}

void
Track::beginBuild(const TrackProfile& profile)
{
    transform_vertices = glm::mat4(1);
    transform_texture_coords = glm::mat3(1);

    vertices_map.clear();
    vertices.clear();
    texture_coords.clear();
    indexes.clear();

    last_profile = appendProfile(profile);
}

void
Track::endBuild()
{
    const glm::vec4 final_position = transform_vertices * glm::vec4(0,0,0,1);
    cout << "final position " << glm::to_string(final_position.xyz()/final_position.w) << endl;
    cout << vertices.size() << " vertices " << map_transforms.size() << " profiles" << endl;
    cout << "length " << map_positions.back() << endl;

    assert( vertices.size() == texture_coords.size() );
    assert( map_positions.size() == map_transforms.size() );

    for (float tt=0; tt<1; tt+=.00025)
        vertices_map.push_back(getPosition(glm::vec2(cos(2*M_PI*50*tt), map_positions.back()*tt), 1));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexes_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof(Indexes::value_type), indexes.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

float
Track::dichotomyLength(const float length_orig) const
{
    assert( map_positions.front() == 0);
    const float length_total = map_positions.back();
    float length = length_orig;

    while (length >= map_positions.back()) length -= map_positions.back();
    while (length < 0) length += map_positions.back();

    size_t left_dichotomy_interval = 0;
    size_t right_dichotomy_interval = map_positions.size()-1;
    while (true)
    {
        const size_t center_dichotomy_interval = (left_dichotomy_interval+right_dichotomy_interval)/2;

        assert( center_dichotomy_interval >= 0 );
        assert( center_dichotomy_interval < map_positions.size()-1 );

        const float left_center_length = map_positions[center_dichotomy_interval];
        const float right_center_length = map_positions[center_dichotomy_interval+1];
        //cout << kk << " " << center_dichotomy_interval << " " << left_center_length << " " << length << " " << right_center_length << endl;

        if (left_center_length > length)
        {
            right_dichotomy_interval = center_dichotomy_interval;
            continue;
        }

        if (right_center_length <= length)
        {
            left_dichotomy_interval = center_dichotomy_interval+1;
            continue;
        }

        return center_dichotomy_interval+ (length-left_center_length)/(right_center_length-left_center_length);
    }

    return 0;
}

glm::mat4
Track::getTransform(const glm::vec2& position) const
{
    const glm::vec2 position_remap((TrackProfile::Transforms::size-1)*(position.x+1)/2., dichotomyLength(position.y));

    const glm::ivec2 position_aa(std::floor(position_remap.x), std::floor(position_remap.y));
    const glm::ivec2 position_bb(std::ceil(position_remap.x), std::ceil(position_remap.y));

    //cout << "prout " << glm::to_string(position_remap) << " " << glm::to_string(position_aa) << " " << glm::to_string(position_bb) << endl;

    assert( position_aa.x >= 0 );
    assert( position_aa.y >= 0 );
    assert( position_bb.x <= TrackProfile::Transforms::size-1 );
    assert( position_bb.y <= map_transforms.size()-1 );

    const float delta_x = position_remap.x-position_aa.x;
    const float delta_y = position_remap.y-position_aa.y;

    assert( delta_x >= 0 );
    assert( delta_y >= 0 );
    assert( delta_x < 1 );
    assert( delta_y < 1 );

    const glm::mat4 accum =
        (1-delta_x) * (1-delta_y) * glm::normalize(map_transforms[position_aa.y][position_aa.x]) +
        delta_x     * delta_y     * glm::normalize(map_transforms[position_bb.y][position_bb.x]) +
        (1-delta_x) * delta_y     * glm::normalize(map_transforms[position_bb.y][position_aa.x]) +
        delta_x     * (1-delta_y) * glm::normalize(map_transforms[position_aa.y][position_bb.x]);

    return accum;
}

glm::vec3
Track::getPosition(const glm::vec2& position, const float height) const
{
    return glm::transform(getTransform(position), glm::vec3(0, height, 0));
}

glm::mat2
Track::getMetric(const glm::vec2& position) const
{
    const float epsilon = 1e-3;
    const glm::vec3 ex = (getPosition(position+glm::vec2(epsilon,0),0)-getPosition(position-glm::vec2(epsilon,0),0))/(2*epsilon);
    const glm::vec3 ey = (getPosition(position+glm::vec2(0,epsilon),0)-getPosition(position-glm::vec2(0,epsilon),0))/(2*epsilon);
    const glm::mat2 first_form(glm::dot(ex,ex), glm::dot(ex,ey), glm::dot(ey,ex), glm::dot(ey,ey));
    return first_form;
}

unsigned int
Track::appendPoint(const glm::vec3& vertex, const glm::vec2& texture_coord)
{
    unsigned int index = vertices.size();

    vertices.push_back(glm::transform(transform_vertices, vertex));
    texture_coords.push_back(glm::transform(transform_texture_coords, texture_coord));

    return index;
}

Track::TrackProfile
Track::appendProfile(const TrackProfile& profile)
{
    TrackProfile profile_copy = profile;

    for (size_t kk=0; kk<TrackProfile::Indexes::size; kk++)
        profile_copy.indexes[kk] = appendPoint(profile.vertices[kk], profile.texture_coords[kk]);

    const glm::vec2 origin = glm::transform(transform_texture_coords, glm::vec2(.5,0));
    assert( origin.x == .5 );
    map_positions.push_back(origin.y);

    TrackProfile::Transforms transformed_transforms;
    for (size_t kk=0; kk<TrackProfile::Transforms::size; kk++)
        transformed_transforms[kk] = transform_vertices * profile_copy.transforms[kk];

    map_transforms.push_back(transformed_transforms);

    return profile_copy;
}

void
Track::extrudeProfile(const TrackProfile& profile_next)
{
    for (unsigned int kk=0; kk<TrackProfile::Indexes::size-1; kk++)
    {
        indexes.push_back(glm::uvec3(last_profile.indexes[kk], last_profile.indexes[kk+1], profile_next.indexes[kk+1]));
        indexes.push_back(glm::uvec3(last_profile.indexes[kk], profile_next.indexes[kk+1], profile_next.indexes[kk]));
    }

    last_profile = profile_next;
}

void
Track::appendFlatWidthChange(const float end_width, const float length, const unsigned int subdiv)
{
    assert( last_profile.isFlat() );
    const float start_width = last_profile.total_width;
    cout << "flat width change piece start_width=" << start_width << " end_width=" << end_width << " length=" << length << endl;

    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        const float width = start_width + (end_width-start_width) * utils::smooth_interp(kk, subdiv);
        const TrackProfile next_profile = appendProfile(TrackProfile::flatProfile(width));
        extrudeProfile(next_profile);
    }
}

void
Track::appendStraight(const float length, const unsigned int subdiv)
{
    cout << "straigth piece length=" << length << endl;

    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        const TrackProfile next_profile = appendProfile(last_profile);
        extrudeProfile(next_profile);
    }
}

void
Track::appendTurn(const float angle, const float length, const unsigned int subdiv)
{
    const float radius = length/angle;
    cout << "turn piece angle=" << angle << " length=" << length << " radius=" << radius << endl;

    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv/2.,0,0)) * glm::rotate(angle/subdiv, glm::vec3(0,1,0)) * glm::translate(glm::vec3(length/subdiv/2.,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        const TrackProfile next_profile = appendProfile(last_profile);
        extrudeProfile(next_profile);
    }
}

void
Track::appendTwist(const float angle, const float length, const unsigned int subdiv)
{
    cout << "twist piece angle=" << angle << " length=" << length << endl;

    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv,0,0)) * glm::rotate(angle*utils::smooth_diff(kk, subdiv), glm::vec3(1,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        const TrackProfile next_profile = appendProfile(last_profile);
        extrudeProfile(next_profile);
    }
}

void
Track::appendQuarter(const float angle, const float length, const unsigned int subdiv)
{
    const float radius = length/angle;
    cout << "quarter piece angle=" << angle << " length=" << length << " radius=" << radius << endl;

    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv/2.,0,0)) * glm::rotate(angle/subdiv, glm::vec3(0,0,1)) * glm::translate(glm::vec3(length/subdiv/2.,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        const TrackProfile next_profile = appendProfile(last_profile);
        extrudeProfile(next_profile);
    }
}

void
Track::appendPipeIn(const float width_total, const float width_flat, const float angle, const float length, const unsigned int subdiv)
{
    assert( last_profile.isFlat() );
    const float width = last_profile.total_width;
    cout << "pipe in piece width_total=" << width_total << " width_flat=" << width_flat << " length=" << length << endl;

    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        const float width_total_interp = width + (width_total-width) * utils::smooth_interp(kk, subdiv);
        const float width_flat_interp = width + (width_flat-width) * utils::smooth_interp(kk, subdiv);
        const float angle_interp = angle * utils::smooth_interp(kk, subdiv);

        const TrackProfile next_profile = appendProfile(TrackProfile::curvedProfile(width_total_interp, width_flat_interp, angle_interp));
        extrudeProfile(next_profile);
    }
}

void
Track::appendPipeOut(const float width, const float length, const unsigned int subdiv)
{
    assert( !last_profile.isFlat() );
    const float width_total = last_profile.total_width;
    const float width_flat = last_profile.flat_width;
    const float angle = last_profile.angle;
    cout << "pipe out piece width=" << width << " length=" << length << endl;

    for (unsigned int kk=0; kk<subdiv; kk++)
    {
        transform_vertices *= glm::translate(glm::vec3(length/subdiv,0,0));
        transform_texture_coords *= glm::translate(glm::vec2(0,length/subdiv/32.));

        const float width_total_interp = width_total + (width-width_total) * utils::smooth_interp(kk, subdiv);
        const float width_flat_interp = width_flat + (width-width_flat) * utils::smooth_interp(kk, subdiv);
        const float angle_interp = angle * (1-utils::smooth_interp(kk, subdiv));

        const TrackProfile next_profile = appendProfile(TrackProfile::curvedProfile(width_total_interp, width_flat_interp, angle_interp));
        extrudeProfile(next_profile);
    }
}

void
Track::draw(const glm::mat4& modelview) const
{
    glm::mat4 modelview_local = modelview;
    //modelview_local = glm::scale(modelview_local, glm::vec3(m_scale, m_scale, m_scale));
    shader_track.setUniform("modelview", modelview_local);
    shader_map.setUniform("modelview", modelview_local);

    {
        glUseProgram(shader_track.getProgramID());

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

    {
        glUseProgram(shader_map.getProgramID());

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices_map.data());
        glEnableVertexAttribArray(0);

        glBindTexture(GL_TEXTURE_2D, texture.getID());

        glDrawArrays(GL_LINE_STRIP, 0, vertices_map.size());

        glBindTexture(GL_TEXTURE_2D, 0);

        glDisableVertexAttribArray(0);

        glUseProgram(0);
    }

}

