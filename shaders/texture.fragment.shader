#version 450 core

in vec4 color;
in vec2 textCoord;

out vec4 fragColor;

uniform sampler2D image;

void main()
{
  fragColor = color * texture(image, textCoord);
}