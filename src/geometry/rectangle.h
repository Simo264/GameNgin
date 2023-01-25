#ifndef RECTANGLE_H
#define RECTANGLE_H


#include <array>

#include "abstract_object.h"

// Rectangle class
// -----------------------------------------------------------
class Rectangle : public ABCobject
{
private:
  /* objects space */
  static const std::array<position_t, 4>  m_localspace;
  static const std::array<uint8_t,    6>  m_indices;
  /* vertex colors */
  std::array<color8_t, 4>  m_colors;

  void init();

public:
  Rectangle(glm::vec2 dimension_, glm::vec2 position_);

  void render(class Shader* shader, uint32_t drawmode = GL_TRIANGLES);

  void setColors(std::array<color8_t, 4> colors);
};

#endif