#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <array>

#include "object_interface.h"

#include "../vertex.h"

class Triangle : public ObjectInterface
{
private:
  /* objects space */
  static const std::array<position_t, 3> m_localspace;

  /* vertex colors */
  std::array<color8_t, 3>   m_colors;

  void init();

public:
  Triangle();
  Triangle(std::array<color8_t, 3> colors);

  void render(class Shader* shader, uint32_t drawmode);
};

#endif