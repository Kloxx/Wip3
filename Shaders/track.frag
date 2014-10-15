// Version du GLSL

#version 150 core


// Entrée

in vec2 coordTexture;


// Uniform

uniform sampler2D tex;
uniform float time;


// Sortie

out vec4 out_Color;


// Fonction main

void main()
{
    // Couleur du pixel

    out_Color = texture(tex, coordTexture);
    if (!(out_Color.r < .01 && out_Color.g < .01 && out_Color.b > .99)) return;

    float lateral_shift = coordTexture.x-.5;
    if (coordTexture.x > 1) lateral_shift = 1.5-coordTexture.x;

    float position = 10*lateral_shift + coordTexture.y - 2*time;
    out_Color = vec4(0,0,mod(position, 1),1);

}
