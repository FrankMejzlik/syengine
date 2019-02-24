#version 330

in vec3 color;
out vec4 colour;

void main()
{
    colour = vec4(color, 1.0f);   
}
