#version 400 core

in vec3 pos;

out vec4 outColor;

void main()
{
    outColor = vec4(pos, 1.0);
}
