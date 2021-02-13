#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <GL/glew.h>

class Display
{
public:
    Display(int width, int height, const std::string& title);

    void Clear(float r, float g, float b, float a);
    void Update();

    bool IsClosed();

    virtual ~Display();

    float h;
    float v;
    float z;
protected:
    bool PLMode = false;
private:

    SDL_Window* m_window;
    SDL_GLContext m_glContext;

    bool m_isClosed;
};

#endif // DISPLAY_H