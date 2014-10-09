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

const float stripes_fraction = 30;
const float stripes_size = 100;

const vec3 planet_position = vec3(1000,-300,200);
const float planet_radius = 400;

void main()
{
  vec4 coordEye = projection_inv * vec4(0,0,0,1);
  vec3 coordDirection = normalize(coordWorld.xyz/coordWorld.w-coordEye.xyz/coordEye.w);

  /***** skybox tetxure *****/
  out_Color = texture(tex, coordTexture);

  /***** stripes *****/
  bool in_strip = mod(gl_FragCoord.x + gl_FragCoord.y + 100*time, stripes_size) < stripes_fraction || mod(gl_FragCoord.x - gl_FragCoord.y + 150*time, stripes_size) < stripes_fraction;
  if (!in_strip) return;

  /***** horizon *****/
  out_Color = vec4(1,0,0,1);
  if (coordDirection.y < 0) out_Color = vec4(0,1,0,1);

  /***** planet *****/
  vec3 coordPlanet = planet_position-coordEye.xyz/coordEye.w;
  float lambda = dot(coordDirection, coordPlanet);
  if (lambda < 0) return;

  float radius = sqrt(dot(coordPlanet, coordPlanet) - lambda*lambda);
  if (radius > planet_radius) return;

  out_Color = vec4(0,0,1,1);
}
