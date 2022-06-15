#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

smooth out vec4 the_color;

void main()
{
    gl_Position = position;
    the_color = color;
}
