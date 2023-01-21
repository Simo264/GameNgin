#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glew.h>
#include <memory>
#include <array>

#include "../vertex_array.h"
#include "../vertex.h"

class Triangle
{
private:
  std::unique_ptr<VertexArray> m_vaOBJ;
  std::unique_ptr<VertexBuffer> m_vbOBJ;

  /* objects space */
  std::array<position_t, 3> m_localspace;
  
  /* vertex colors */
  std::array<color8_t, 3> m_colors;

  void init();

public:
  Triangle();
  Triangle(std::array<position_t, 3> localspace, std::array<color8_t, 3> colors);
  ~Triangle() = default;

  void render(class Shader* shader);
};



#endif