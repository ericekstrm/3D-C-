#version 400 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform mat4 projection;
uniform mat4 camera_matrix;
uniform mat4 world_matrix;

out vec3 color;

void main()
{
	gl_Position = projection * camera_matrix * world_matrix * vec4(aPos, 1.0);
	color = aColor;
}
