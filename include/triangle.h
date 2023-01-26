#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>
#include "object.h"


// Triangle class
// -----------------------------------------------------------
class Triangle : public Object
{
private:
  /* objects space */
  static const std::array<position_t, 3>  m_localspace;
  /* vertex colors */
  static const std::array<color8_t, 3>    m_colors;

  void init();

public:
  Triangle(glm::vec2 dimension_, glm::vec2 position_);

  void render(class Shader* shader, uint32_t drawmode = GL_TRIANGLES);

  void setColors(std::array<color8_t, 3> colors);
};
// -----------------------------------------------------------

#endif