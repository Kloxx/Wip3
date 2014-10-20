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
#include <glm/gtx/transform.hpp>

namespace glm
{

template <typename T, precision P>
detail::tmat3x3<T,P>
translate(const detail::tvec2<T,P> vec)
{
    typedef detail::tmat3x3<T,P> mat3;
    mat3 mat_trans(1);
    mat_trans[2][0] = vec[0];
    mat_trans[2][1] = vec[1];
    return mat_trans;
}

template <typename T, precision P>
detail::tvec2<T,P>
transform(const detail::tmat3x3<T,P> matrix, const detail::tvec2<T,P> vertex)
{
    typedef detail::tvec3<T,P> vec3;
    const vec3 vertex_homo(vertex,1);
    const vec3 vertex_transformed_homo = matrix * vertex_homo;
    return vertex_transformed_homo.xy()/vertex_transformed_homo.z;
}

template <typename T, precision P>
detail::tvec3<T,P>
transform(const detail::tmat4x4<T,P> matrix, const detail::tvec3<T,P> vertex)
{
    typedef detail::tvec4<T,P> vec4;
    const vec4 vertex_homo(vertex,1);
    const vec4 vertex_transformed_homo = matrix * vertex_homo;
    return vertex_transformed_homo.xyz()/vertex_transformed_homo.w;
}

}

namespace utils
{

float
linspace(const unsigned int kk, const unsigned int kk_max, const float min_value, const float max_value);

float
smooth_function(const float xx);

float
smooth_interp(const unsigned int kk, const unsigned int kk_max);

float
smooth_diff(const unsigned int kk, const unsigned int kk_max);

}


// std library
#include <string>
#include <cassert>

