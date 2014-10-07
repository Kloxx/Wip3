#include "SceneOpenGL.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <string>

SceneOpenGL::SceneOpenGL(std::string windowTitle, int windowWidth, int windowHeight, bool fullscreen) :
    m_windowTitle(windowTitle), m_windowWidth(windowWidth), m_windowHeight(windowHeight),
    m_fullscreen(fullscreen), m_window(0), m_GLContext(0), m_input()
{
}

SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(m_GLContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool SceneOpenGL::initWindow()
{
    if(SDL_Init(SDL_INIT_VIDEO<0))
    {
        std::cout << "Error while initializing SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if(m_fullscreen)
        m_window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN);
    else
        m_window = SDL_CreateWindow(m_windowTitle.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);

    if(m_window == 0)
    {
        std::cout << "Error while creating window : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }

    m_GLContext = SDL_GL_CreateContext(m_window);

    if(!m_GLContext)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }

    return true;
}

bool SceneOpenGL::initGL()
{
    #ifdef WIN32
    GLenum initGLEW( glewInit() );

    if(initGLEW != GLEW_OK)
    {
        std::cout << "Error while initializing GLEW : " << glewGetErrorString(initGLEW) << std::endl;
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }
    #endif // WIN32

    glEnable(GL_DEPTH_TEST);

    return true;
}

void SceneOpenGL::mainLoop()
{
    using namespace glm;

    unsigned int frameRate(1000/60);
    Uint32 startLoop(0), elapsed(0);
    Shader shader("Shaders/texture.vert", "Shaders/texture.frag");
    shader.charger();
    Uint32 startProgram(SDL_GetTicks());
    int frames(0);

    //********** For test **********
    float verticesFloor[] = {
        0,0,-15, 500,0,-15, 500,0,20,
        0,0,-15, 0,0,20, 500,0,20,
        460,0,20, 500,0,20, 500,0,500,
        460,0,20, 460,0,500, 500,0,500
    };
    float textureFloor[] = {
        0,0, 50,0, 50,5,
        0,0, 0,5, 50,5,
        0,0, 5,0, 5,50,
        0,0, 0,50, 5,50
    };
    //********** For test **********

    mat4 projection;
    mat4 modelview;
    mat4 modelviewSave;

    projection = perspective(70.0, (double) m_windowWidth/m_windowHeight, 0.01, 600.0);
    modelview = mat4(1.0);

    Ship ship(shader, "Models/ship.png", vec3(0,1,0), 0.014, 2.0, 900.0);
    //Ship ship2(shader, "Models/ship.png", vec3(0,1,0), 0.015, 2.0, 1000.0);
    //Ship ship3(shader, "Models/ship.png", vec3(0,1,0), 0.016, 2.0, 1100.0);
    //Ship ship4(shader, "Models/ship.png", vec3(0,1,0), 0.017, 2.0, 1200.0);
    CameraThirdPerson camera(8.0, 3.0, vec3(0,1,0));

    m_input.afficherPtr(true);
    m_input.capturePtr(false);

    Texture texture("Textures/metal029b.jpg");
    texture.load();
    modelviewSave = modelview;

    while(!m_input.terminate())
    {
        startLoop = SDL_GetTicks();
        m_input.updateEvents();

        if(m_input.getKey(SDL_SCANCODE_ESCAPE))
            break;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Test
        glUseProgram(shader.getProgramID());
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, verticesFloor);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, textureFloor);
            glEnableVertexAttribArray(2);
            glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));
            glUniformMatrix4fv(glGetUniformLocation(shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
            glBindTexture(GL_TEXTURE_2D, texture.getID());
            glDrawArrays(GL_TRIANGLES, 0, 12);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisableVertexAttribArray(1);
            glDisableVertexAttribArray(0);
        glUseProgram(0);

        // Render
        modelviewSave = modelview;

        ship.control(m_input);
        ship.draw(projection, modelview);

        //modelview = modelviewSave;

        //ship2.control(m_input);
        //ship2.draw(projection, modelview);

        //modelview = modelviewSave;

        //ship3.control(m_input);
        //ship3.draw(projection, modelview);

        //modelview = modelviewSave;

        //ship4.control(m_input);
        //ship4.draw(projection, modelview);

        modelview = modelviewSave;
        camera.lookAt(modelview, ship);

        // Actualization
        SDL_GL_SwapWindow(m_window);

        // Framerate
        elapsed = SDL_GetTicks() - startLoop;
        if(elapsed < frameRate)
            SDL_Delay(frameRate - elapsed);
            frames++;
    }
    Uint32 stopProgram(SDL_GetTicks());
    double frameRateAvg = frames / ((double) stopProgram/1000 - (double) startProgram/1000);
    std::cout << "Ran for " << (double) stopProgram/1000 - (double) startProgram/1000 << "s" << std::endl;
    std::cout << "Frames : " << frames << std::endl;
    std::cout << "Framerate : " << frameRateAvg << std::endl;
}
