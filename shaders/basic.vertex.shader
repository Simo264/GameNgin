#version 450 core

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec3 inColor;

out vec4 color;
out vec2 textCoord;

uniform mat4 model;
uniform mat4 projection;

void main()
{
  color         = vec4(inColor, 1);
  gl_Position = projection * model * vec4(inPosition, 1.0, 1.0);
}