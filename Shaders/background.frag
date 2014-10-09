// Version du GLSL

#version 150 core


// Entrée

in vec2 coordTexture;
in vec4 coordWorld;


// Uniform

uniform sampler2D tex;
uniform float time;
uniform vec4 projection_inv;


// Sortie 

out vec4 out_Color;


// Fonction main

void main()
{
  vec4 coordEye = projection_inv * vec4(0,0,0,1);
  vec4 coordDirection = coordWorld/coordWorld.w - coordEye/coordEye.w;
  coordDirection.w = 1;
  //vec4 absCoordWorld = normalize(abs(coordWorld));

  //out_Color = vec4(coordWorld.x/coordWorld.w,0,0,1);
  //out_Color = vec4(gl_FragCoord.x/1024., 0,0, 1);
  out_Color = texture(tex, coordTexture);

  /***** stripes *****/
  bool in_strip = mod(gl_FragCoord.x + gl_FragCoord.y + 100*time, 100) > 50;
  if (in_strip) {
    out_Color = vec4(1,0,0,1);
    if (coordDirection.z > 0) out_Color = vec4(0,1,0,1);
  }
}
