#pragma once

#include "Array.h"

template <size_t additional_vertices>
struct Profile
{
    typedef Profile<additional_vertices> Self;
    typedef Array<glm::mat4, additional_vertices+2> Transforms;

    Profile(const float total_width, const float flat_width, const float angle, const Transforms& transforms);

    static
    Self
    flatProfile(const float width);

    static
    Self
    curvedProfile(const float width, const float flat_width, const float angle);

    bool
    isFlat() const;

    typedef Array<std::pair<glm::vec3, glm::vec2>, 7> Border;
    typedef Array<glm::vec3, 1+2*(Border::size+additional_vertices)> Vertices;
    typedef Array<glm::vec2, Vertices::size> TextureCoords;
    typedef Array<unsigned int, Vertices::size> Indexes;

    float total_width;
    float flat_width;
    float angle;
    Transforms transforms;
    Vertices vertices;
    TextureCoords texture_coords;
    Indexes indexes;

protected:

    static
    Border
    getLeftBorder();

    static
    Border
    getRightBorder();
};

#include "Profile.ih"

