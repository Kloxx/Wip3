#include "SceneOpenGL.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
    SceneOpenGL scene("Yo, dawg !", 1440, 900, false);

    if(!scene.initWindow())
        return -1;
    if(!scene.initGL())
        return -1;

    scene.mainLoop();

    return 0;
}
