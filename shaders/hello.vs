#version 330 core
layout (location = 0) in vec3 aPos;
out vec4 pos;

void main()
{
    pos = vec4(aPos.xyz / 0.5, 1.0);
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ;
}
