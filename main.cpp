#include "Options.h"
#include "SceneOpenGL.h"

#include <iostream>

int main(int argc, char *argv[])
{
    Options options(argc, argv);
    std::cout << options << std::endl;

    SceneOpenGL scene(options);

    if(!scene.initWindow("Yo, dawg!! :)")) return -1;
    if(!scene.initGL()) return -1;

    scene.mainLoop();

    return 0;
}
