#version 410 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform vec2 offset;

smooth out vec4 the_color;

void main()
{
    vec4 total_offset = vec4(offset.x, offset.y, 0.0, 0.0);
    gl_Position = position + total_offset;
    the_color = color;
}
