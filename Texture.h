#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#ifdef WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#endif // WIN32

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

class Texture
{
public:
    Texture();
    Texture(std::string imageFile);
    Texture(Texture const &textureToCopy);
    ~Texture();
    Texture &operator=(Texture const &textureToCopy);
    bool load();
    GLuint getID() const;
    void setImageFile(const std::string &imageFile);
    SDL_Surface *invertPixels(SDL_Surface *sourceImage) const;

private:
    GLuint m_id;
    std::string m_imageFile;
};

#endif // TEXTURE_H_INCLUDED
