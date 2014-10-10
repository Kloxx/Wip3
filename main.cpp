#include "SceneOpenGL.h"

int main(int argc, char *argv[])
{
    SceneOpenGL scene("Yo, dawg !", WINDOW_WIDTH, WINDOW_HEIGHT, false);

    if(!scene.initWindow())
        return -1;
    if(!scene.initGL())
        return -1;

    scene.mainLoop();

    return 0;
}
