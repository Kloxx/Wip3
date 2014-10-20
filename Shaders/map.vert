// Version du GLSL

#version 150 core


// Entrées

in vec3 in_Vertex;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;
uniform mat4 map_transforms;
uniform uvec2 map_transform_size;

void main()
{
    gl_Position = projection * modelview * vec4(in_Vertex, 1.0);
}
