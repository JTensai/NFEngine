#version 120

varying vec2 texture_coordinate0;
varying vec3 normal0;

uniform sampler2D diffuse;

vec3 lighting_direction;

void main(){

	// Set color of shader
	// gl_FragColor = vec4(0, 1.0, 0, 1.0);
	
	lighting_direction = vec3(0,0,1);
	gl_FragColor = texture2D(diffuse, texture_coordinate0) * clamp(dot(-lighting_direction, normal0), 0.0, 1.0);
}