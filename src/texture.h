#ifndef TEXTURE_H
#define TEXTURE_H

#include <cassert>
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <SDL2/SDL_image.h>

class Texture
{
private:
    GLuint m_texture;
public:
    Texture(const std::string& fileName);

    void Bind(unsigned int unit);

    ~Texture();
};

#endif
