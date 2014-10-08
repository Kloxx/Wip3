#pragma once

// OpenGL
#ifdef WIN32
#include <GL/glew.h>
#elif __APPLE__
#define GL3_PROTOTYPES 1
#include <OpenGL/gl3.h>
#else
#define GL3_PROTOTYPES 1
#include <GLES3/gl3.h>
#endif

// GLM
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

// std library
#include <string>

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900

