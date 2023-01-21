#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <array>

#include "../vertex_array.h"
#include "../vertex.h"

class Triangle
{
private:
  std::unique_ptr<VertexArray>  m_vaOBJ;
  std::unique_ptr<VertexBuffer> m_vbOBJ;
  /* objects space */
  std::array<position_t, 3> m_localspace;
  /* vertex colors */
  std::array<color8_t, 3>   m_colors;

  /* model space */
  glm::mat4 m_scalemat   = glm::mat4(1.f);
  glm::mat4 m_rotatemat  = glm::mat4(1.f);
  glm::mat4 m_transmat   = glm::mat4(1.f);

  void init();

public:
  Triangle();
  Triangle(std::array<position_t, 3> localspace, std::array<color8_t, 3> colors);
  ~Triangle() = default;

  void scale(float x, float y);
  void rotate(float angle);
  void translate(float x, float y);

  void render(class Shader* shader);
};



#endif