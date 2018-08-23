#version 330 core
out vec4 color;

uniform vec3 myColor;

void main()
{
	color = vec4(myColor, 1.0f);
}