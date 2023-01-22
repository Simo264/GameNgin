#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <array>

#include "object_interface.h"
#include "../vertex.h"

class Rectangle : public ObjectInterface
{
private:
  std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ;

  /* objects space */
  static const std::array<position_t, 4> m_localspace;
  static const std::array<uint8_t, 6> m_indices;
  
  /* vertex colors */
  std::array<color8_t, 4>   m_colors;

  void init();

public:
  Rectangle();
  Rectangle(std::array<color8_t, 4> colors);

  void render(class Shader* shader, uint32_t drawmode = GL_TRIANGLES);
};

#endif