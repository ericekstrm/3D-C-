#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 projection;

out vec3 pos;

void main()
{
	gl_Position = projection * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	pos = gl_Position.xyz;
}