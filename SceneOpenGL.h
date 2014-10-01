#ifndef SCENEOPENGL_H_INCLUDED
#define SCENEOPENGL_H_INCLUDED

// OpenGL
#ifdef WIN32
#include <GL/glew.h>
#else
#define GL_PROTOTYPES 1
#include <GL3/gl3.h>
#endif // WIN32

// GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other
#include <SDL2/SDL.h>
#include <iostream>
#include "Shader.h"
#include <string>
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
};

#endif // SCENEOPENGL_H_INCLUDED
