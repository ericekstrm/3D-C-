#version 400 core

in vec3 inPosition;


void main()
{
	gl_Position = vec4(inPosition, 1);
}