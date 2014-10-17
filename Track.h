#pragma once

#include "common.h"
#include "Shader.h"
#include "Texture.h"
#include "Array.h"

#include <vector>
#include <list>
#include <map>

struct Track
{
    Track(const Shader& shader, const std::string& texture);

    void
    draw(const glm::mat4& modelview) const;

    void
    appendStraight(const float start_width, const float end_width, const float length, const unsigned int subdiv = 16);

    void
    appendTurn(const float width, const float angle, const float length, const unsigned int subdiv=16);

    void
    appendTwist(const float width, const float angle, const float length, const unsigned int subdiv=16);

    void
    appendQuarter(const float width, const float angle, const float length, const unsigned int subdiv=16);

    void
    clear();

    void
    build();

protected:

    struct Profile
    {
        Profile(const float& width, Track& track);

        void
        extrude(const Profile& profile, Track& track) const;

    protected:

        typedef Array<unsigned int, 14> Indexes;
        Indexes indexes;

    };

    unsigned int
    appendPoint(const glm::vec3& vertex, const glm::vec2& texture_coord);

    float
    registerTransform();

    Shader shader;
    Texture texture;

    typedef std::map<float, glm::mat4> Transforms;

    Transforms transforms;

    typedef std::vector<glm::vec3> Vertices;
    typedef std::vector<glm::vec2> TextureCoords;
    typedef std::vector<glm::uvec3> Indexes;

    Vertices vertices;
    TextureCoords texture_coords;
    Indexes indexes;

    glm::mat4 transform_vertices;
    glm::mat3 transform_texture_coords;

    GLuint indexes_buffer;

};


