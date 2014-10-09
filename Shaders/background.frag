// Version du GLSL

#version 150 core


// Entrée

in vec2 coordTexture;
in vec4 coordWorld;


// Uniform

uniform sampler2D tex;
uniform float time;
uniform mat4 projection;
uniform mat4 projection_inv;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
  vec4 coordEye = projection_inv * vec4(0,0,0,1);
  vec3 coordDirection = normalize(coordWorld.xyz/coordWorld.w-coordEye.xyz/coordEye.w);
  //vec4 absCoordWorld = normalize(abs(coordWorld));

  //out_Color = vec4(coordWorld.x/coordWorld.w,0,0,1);
  //out_Color = vec4(gl_FragCoord.x/1024., 0,0, 1);
  out_Color = texture(tex, coordTexture);

  /***** stripes *****/
  bool in_strip = mod(gl_FragCoord.x + gl_FragCoord.y + 100*time, 100) < 20 || mod(gl_FragCoord.x - gl_FragCoord.y + 150*time, 100) < 20;
  if (!in_strip) return;

  out_Color = vec4(1,0,0,1);
  if (coordDirection.y < 0) out_Color = vec4(0,1,0,1);
}
