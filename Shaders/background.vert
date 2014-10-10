// Version du GLSL

#version 150 core


// Entrées

in vec3 in_Vertex;
in vec2 in_TexCoord0;


// Uniform

uniform mat4 projection;
uniform mat4 modelview;


// Sortie

out vec2 coordTexture;
out vec4 coordWorld;


// Fonction main

void main()
{
    // Position finale du vertex en 3D

    coordWorld = modelview * vec4(in_Vertex, 1.0);
    gl_Position = projection * coordWorld;

    // Envoi des coordonnées de texture au Fragment Shader

    coordTexture = in_TexCoord0;
}
