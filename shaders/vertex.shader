#version 450 core

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec3 inColor;
//layout (location = 2) in vec2 inTextCoord;

out vec4 color;
out vec2 textCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
  gl_Position = projection * view * model * vec4(inPosition, 1.0, 1.0);
  color       = vec4(inColor, 1);
  //textCoord   = inTextCoord;
}