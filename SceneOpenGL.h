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
#include "Options.h"
#include "Track.h"

class SceneOpenGL
{
public:
    SceneOpenGL(const Options& options);
    ~SceneOpenGL();

    bool initWindow(const std::string& windowTitle);
    void initController();
    bool initGL();
    void mainLoop();

private:
    std::string m_windowTitle;
    Options m_options;

    SDL_Window* m_window;
    SDL_GLContext m_GLContext;
    SDL_Event m_event;
    Input m_input;
    bool m_useJoysticks;
};

#endif // SCENEOPENGL_H_INCLUDED
