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

const float pi = 3.1415926535897932384626433832795;
const float stripes_fraction = 8;
const float stripes_size = 10;

const vec3 planet_position = vec3(5000,-1000,1000);
const float planet_radius = 1800;
const float planet_radius_squared = planet_radius*planet_radius;

const float sun_angle = pi/180*2;
const mat3 ecliptic_transform = mat3(1,0,0,0,1,.5,0,-.5,1);

void main()
{
  vec4 coordEye = projection_inv * vec4(0,0,0,1);
  vec3 coordDirection = normalize(coordWorld.xyz/coordWorld.w-coordEye.xyz/coordEye.w);

  /***** skybox tetxure *****/
  out_Color = texture(tex, coordTexture);

  /***** stripes *****/
  bool in_strip = mod(gl_FragCoord.x + gl_FragCoord.y + 100*time, stripes_size) < stripes_fraction || mod(gl_FragCoord.x - gl_FragCoord.y + 150*time, stripes_size) < stripes_fraction;

  /***** horizon *****/
  if (in_strip) out_Color = vec4(0,0,0,1);

  vec3 sun_light_direction = normalize(ecliptic_transform * vec3(cos(1.5*time),0,sin(1.5*time)));
  if (dot(sun_light_direction, coordDirection)>cos(sun_angle)) out_Color = vec4(1,1,0,1);

  /***** planet *****/
  vec3 coordPlanet = planet_position-coordEye.xyz/coordEye.w;
  float lambda = dot(coordDirection, coordPlanet);
  if (lambda < 0) return;

  float radius_squared = dot(coordPlanet, coordPlanet) - lambda*lambda;
  if (radius_squared > planet_radius_squared) return;

  float lambda_prime = sqrt(planet_radius_squared-radius_squared);
  vec3 normal = normalize((lambda-lambda_prime)*coordDirection - coordPlanet);
  //vec3 reflection = coordDirection - 2*dot(normal,coordDirection)*normal;

  //out_Color = vec4(dot(reflection, sun_light_direction)>0,dot(normal,sun_light_direction)>0,1,1);
  out_Color = vec4(1,dot(normal,sun_light_direction)>0,1,1);
  if (fract(asin(normal.y)*32/(pi*2)) > .5) out_Color.b = 0;
}
