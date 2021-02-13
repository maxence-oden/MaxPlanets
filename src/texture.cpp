#include "texture.h"


int mode=GL_RGB;

Texture::Texture(const std::string& fileName)
{
    SDL_Surface* image_surface = IMG_Load(fileName.c_str());

    if (!image_surface) {
        std::cerr << "Texture failed to load for texture:" << fileName << std::endl;
    }
    if(image_surface->format->BitsPerPixel>=4)
        mode=GL_RGBA;

    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_surface->w, image_surface->h, 0, mode, GL_UNSIGNED_BYTE, image_surface->pixels);

    SDL_FreeSurface(image_surface);
}

Texture::~Texture()
{
    glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
    assert(unit <= 31);

    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}