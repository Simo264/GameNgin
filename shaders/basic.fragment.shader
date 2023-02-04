#version 450 core

in  vec4 color;
out vec4 fragColor;

uniform sampler2D uf_texture;

void main()
{
  fragColor = color;
}