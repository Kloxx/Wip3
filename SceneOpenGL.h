#ifndef SCENEOPENGL_H_INCLUDED
#define SCENEOPENGL_H_INCLUDED

#include "common.h"

// Other
#include <SDL2/SDL.h>
#include "Shader.h"
#include "Cube.h"
#include "Input.h"
#include "Texture.h"
#include "Camera.h"
#include "Ship.h"

class SceneOpenGL
{
public:
    SceneOpenGL(std::string windowTitle, int windowWidth, int windowHeight, bool fullscreen);
    ~SceneOpenGL();

    bool initWindow();
    void initController();
    bool initGL();
    void mainLoop();

private:
    std::string m_windowTitle;
    int m_windowWidth;
    int m_windowHeight;
    bool m_fullscreen;

    SDL_Window* m_window;
    SDL_GLContext m_GLContext;
    SDL_Event m_event;
    Input m_input;
    bool m_useJoysticks;
};

#endif // SCENEOPENGL_H_INCLUDED
