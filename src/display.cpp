#include "display.h"

//Construction
Display::Display(int width, int height, const std::string &title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    m_glContext = SDL_GL_CreateContext(m_window);

    GLenum status = glewInit();

    if (status != GLEW_OK)
    {
        std::cerr << "Glew failed to initialize!" << std::endl;
    }

    m_isClosed = false;

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    v = 0;
    h = 0;
    z = 0;
    PLMode = false;
}

//Destruction
Display::~Display()
{
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


void Display::Clear(float r, float g, float b, float a)
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Update()
{
    SDL_GL_SwapWindow(m_window);

    SDL_Event e;
    if (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            m_isClosed = true;
        if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
                h = -0.01;
                break;
            case SDLK_RIGHT:
                h = 0.01;
                break;
            case SDLK_UP:
                v = 0.01;
                break;
            case SDLK_DOWN:
                v = -0.01;
                break;
            case SDLK_z:
                z = 0.2;
                break;
            case SDLK_s:
                z = -0.2;
                break;
            case SDLK_p:
                if (PLMode) {
                    PLMode = false;
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
                else
                {
                    PLMode = true;
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
                break;
            
            default:
                break;
            }
        }
        if (e.type == SDL_KEYUP)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_LEFT:
                h = 0;
                break;
            case SDLK_RIGHT:
                h = 0;
                break;
            case SDLK_UP:
                v = 0;
                break;
            case SDLK_DOWN:
                v = 0;
                break;
            case SDLK_z:
                z = 0;
                break;
            case SDLK_s:
                z = 0;
                break;
            default:
                break;
            }
        }
    }
}
bool Display::IsClosed()
{
    return m_isClosed;
}