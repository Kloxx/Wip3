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
#define GLM_SWIZZLE
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

namespace glm
{

template <typename T, precision P>
detail::tmat3x3<T,P>
translate(const detail::tvec2<T,P>& vec)
{
    typedef detail::tmat3x3<T,P> mat3;
    mat3 mat_trans(1);
    mat_trans[2][0] = vec[0];
    mat_trans[2][1] = vec[1];
    return mat_trans;
}

}

// std library
#include <string>

#define WINDOW_WIDTH 1440
#define WINDOW_HEIGHT 900

