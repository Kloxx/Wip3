#pragma once

#include "common.h"
#include "Shader.h"
#include "Texture.h"

#include <vector>
#include <list>

typedef std::vector<glm::vec3> Vertices;
typedef std::vector<glm::vec2> TextureCoords;
typedef std::vector<glm::uvec3> Indexes;

struct Piece
{
    virtual
    void
    fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const = 0;
};

struct PieceStraight : public Piece
{
    PieceStraight(const float start_width, const float end_width, const float length);

    void
    fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const;

protected:

    float start_width;
    float end_width;
    float length;
};

struct PieceTurn : public Piece
{
    PieceTurn(const float width, const float angle, const float length, const unsigned int subdiv=16);

    virtual
    void
    fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const;

protected:

    float width;
    float angle;
    float length;
    unsigned int subdiv;
};

struct PieceTwist : public Piece
{
    PieceTwist(const float width, const float angle, const float length, const unsigned int subdiv=16);

    virtual
    void
    fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const;

protected:

    float width;
    float angle;
    float length;
    unsigned int subdiv;
};

struct PieceQuarter : public Piece
{
    PieceQuarter(const float width, const float angle, const float length, const unsigned int subdiv=16);

    virtual
    void
    fillBuffers(glm::mat4& transform, Vertices& vertices, TextureCoords& texture_coords, Indexes& indexes) const;

protected:

    float width;
    float angle;
    float length;
    unsigned int subdiv;
};

struct Track
{
    typedef std::list<Piece*> Pieces;

    Track(const Shader& shader, const std::string& texture, Pieces& pieces);

    void
    draw(const glm::mat4& modelview) const;

protected:

    Shader shader;
    Texture texture;
    Vertices vertices;
    TextureCoords texture_coords;
    Indexes indexes;

    GLuint indexes_buffer;

};


