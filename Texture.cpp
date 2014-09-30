#include "Texture.h"

Texture::Texture(std::string imageFile) : m_id(0), m_imageFile(imageFile){}

Texture::Texture() : m_id(0), m_imageFile(""){}

Texture::Texture(Texture const &textureToCopy)
{
    m_imageFile = textureToCopy.m_imageFile;
    load();
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

Texture& Texture::operator=(Texture const &textureToCopy)
{
    m_imageFile = textureToCopy.m_imageFile;
    load();

    return *this;
}

bool Texture::load()
{
    SDL_Surface *imageSDL = IMG_Load(m_imageFile.c_str());

    if(!imageSDL)
    {
        std::cout << "Error : " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_Surface *invertedImage = invertPixels(imageSDL);
    SDL_FreeSurface(imageSDL);

    if(glIsTexture(m_id) == GL_TRUE)
        glDeleteTextures(1, &m_id);

    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);

    GLenum internalFormat(0);
    GLenum format(0);

    if(invertedImage->format->BytesPerPixel == 3)
    {
        internalFormat = GL_RGB;
        if(invertedImage->format->Rmask == 0xff)
        {
            format = GL_RGB;
        }
        else
        {
            format = GL_BGR;
        }
    }
    else if(invertedImage->format->BytesPerPixel == 4)
    {
        internalFormat = GL_RGBA;
        if(invertedImage->format->Rmask == 0xff)
        {
            format = GL_RGBA;
        }
        else
        {
            format = GL_BGRA;
        }
    }
    else
    {
        std::cout << "Error, texture format not recognized" << std::endl;
        SDL_FreeSurface(invertedImage);

        return false;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, invertedImage->w, invertedImage->h, 0, format, GL_UNSIGNED_BYTE, invertedImage->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, 0);

    SDL_FreeSurface(invertedImage);
    return true;
}

GLuint Texture::getID() const
{
    return m_id;
}

void Texture::setImageFile(const std::string &imageFile)
{
    m_imageFile = imageFile;
}

SDL_Surface* Texture::invertPixels(SDL_Surface *sourceImage) const
{
    SDL_Surface *invertedImage = SDL_CreateRGBSurface(0, sourceImage->w, sourceImage->h, sourceImage->format->BitsPerPixel,
                                                     sourceImage->format->Rmask, sourceImage->format->Gmask, sourceImage->format->Bmask, sourceImage->format->Amask);

    unsigned char* sourcePixels = (unsigned char*) sourceImage->pixels;
    unsigned char* invertedPixels = (unsigned char*) invertedImage->pixels;

    for(int i=0; i<sourceImage->h; i++)
    {
        for(int j=0; j<sourceImage->w * sourceImage->format->BytesPerPixel; j++)
            invertedPixels[(sourceImage->w * sourceImage->format->BytesPerPixel * (sourceImage->h -1 - i)) + j] =
            sourcePixels[(sourceImage->w * sourceImage->format->BytesPerPixel * i) + j];
    }

    return invertedImage;
}
