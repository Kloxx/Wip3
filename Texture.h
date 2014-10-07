#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include "common.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Texture
{
public:
    Texture();
    ~Texture();
    Texture(const std::string& imageFile);

    GLuint getID() const;

protected:
    static SDL_Surface* invertPixels(SDL_Surface* sourceImage);
    bool load();

    GLuint m_id;
    std::string m_imageFile;
};

#endif // TEXTURE_H_INCLUDED
