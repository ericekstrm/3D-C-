#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 camera_matrix;
uniform mat4 world_matrix;

out vec3 pos;

void main()
{
	gl_Position = projection * world_matrix * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	pos = aPos;
}
