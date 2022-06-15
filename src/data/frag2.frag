#version 410 core

smooth in vec4 the_color;

out vec4 output_color;

void main()
{
    output_color = the_color;
}
