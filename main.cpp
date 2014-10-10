#include "Options.h"
#include "SceneOpenGL.h"

#include <iostream>

int main(int argc, char *argv[])
{
		ConfigFile config;

		config.parseIniFile("config.ini");
		config.parseIniFile("../config.ini");
		if (argc > 1) config.parseIniFile(argv[1]);

		std::cout << "********************" << std::endl;
		config.dump(std::cout);
		std::cout << "********************" << std::endl;
		std::cout << config.get("display", "fullscreen", false) << std::endl;

    SceneOpenGL scene("Yo, dawg !", WINDOW_WIDTH, WINDOW_HEIGHT, false);

    if(!scene.initWindow())
        return -1;
    if(!scene.initGL())
        return -1;

    scene.mainLoop();

    return 0;
}
