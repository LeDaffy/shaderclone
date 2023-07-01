#version 460 core
layout (location = 0) in vec3 aPos;
out vec4 coord;

void main()
{
    coord = vec4(aPos, 1.0);
    gl_Position = vec4(aPos, 1.0);
}
