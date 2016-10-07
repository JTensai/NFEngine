#version 120

attribute vec3 position;
attribute vec2 texture_coordinate;
attribute vec3 normal;

varying vec2 texture_coordinate0;
varying vec3 normal0;

uniform mat4 transform;

void main(){
	gl_Position = transform * vec4(position, 1.0);
	texture_coordinate0 = texture_coordinate;
	texture_coordinate0.y = 1 - texture_coordinate0.y;
	normal0 = (transform * vec4(normal, 0.0)).xyz;
}