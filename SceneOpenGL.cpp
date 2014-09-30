#include "SceneOpenGL.h"

SceneOpenGL::SceneOpenGL(std::string windowTitle, int windowWidth, int windowHeight, bool fullscreen) :
    m_windowTitle(windowTitle), m_windowWidth(windowWidth), m_windowHeight(windowHeight),
    m_fullscreen(fullscreen), m_window(0), m_GLContext(0), m_input()
{}

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

    mat4 projection;
    mat4 modelview;
    mat4 modelviewSave;

    projection = perspective(70.0, (double) m_windowWidth/m_windowHeight, 0.01, 300.0);
    modelview = mat4(1.0);
    modelview = lookAt(vec3(3,3,3), vec3(0,0,0), vec3(0,1,0));

    Box box(2.0, "Shaders/texture.vert", "Shaders/texture.frag", "Textures/metal029.jpg");
    CameraDoom camera(vec3(0,1.5,0), vec3(1,0,0), vec3(0,1,0), 1, 5);

    m_input.afficherPtr(false);
    m_input.capturePtr(true);

    while(!m_input.terminate())
    {
        startLoop = SDL_GetTicks();
        m_input.updateEvents();

        if(m_input.getKey(SDL_SCANCODE_ESCAPE))
            break;

        camera.movement(m_input);
        camera.lookAt(modelview);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Camera
        modelviewSave = modelview;

        // Render
        box.afficher(projection, modelview);

        // Actualization
        SDL_GL_SwapWindow(m_window);

        // Framerate
        elapsed = SDL_GetTicks() - startLoop;
        if(elapsed < frameRate)
            SDL_Delay(frameRate - elapsed);
    }
}
