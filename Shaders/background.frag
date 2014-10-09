// Version du GLSL

#version 150 core


// Entrée

in vec2 coordTexture;
in vec4 coordWorld;


// Uniform

uniform sampler2D tex;
uniform float time;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
  // Couleur du pixel

  //out_Color = texture(tex, coordTexture);
  //out_Color = vec4(coordWorld.x/coordWorld.w,0,0,1);
  //out_Color = vec4(gl_FragCoord.x/1024., 0,0, 1);
  bool in_strip = mod(gl_FragCoord.x + gl_FragCoord.y + 300*time, 100) > 50;
  if (in_strip) out_Color = vec4(1,1,0,1);
  else out_Color = vec4(1,0,0,1);
}
