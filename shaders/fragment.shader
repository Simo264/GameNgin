#version 450 core

in vec4 color;
//in vec2 textCoord;

out vec4 fragColor;

uniform sampler2D uf_texture;

void main()
{
  //fragColor = texture(s_texture, textCoord) * color;
  fragColor = color;
}