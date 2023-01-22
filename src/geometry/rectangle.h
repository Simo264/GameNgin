#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <array>

#include "../vertex_array.h"
#include "../vertex.h"

class Rectangle
{
private:
  std::unique_ptr<VertexArray>  m_vaOBJ;
  std::unique_ptr<Buffer<GL_ARRAY_BUFFER>> m_vbOBJ;
  std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ;

  /* objects space */
  static const std::array<position_t, 4> m_localspace;
  static const std::array<uint8_t, 6> m_indices;
  
  /* vertex colors */
  std::array<color8_t, 4>   m_colors;

  /* model space */
  glm::mat4 m_scalemat   = glm::mat4(1.f);
  glm::mat4 m_rotatemat  = glm::mat4(1.f);
  glm::mat4 m_transmat   = glm::mat4(1.f);

  void init();

public:
  Rectangle();
  Rectangle(std::array<color8_t, 4> colors);
  ~Rectangle() = default;

  void scale(float x, float y);
  void rotate(float angle);
  void translate(float x, float y);

  void render(class Shader* shader, uint32_t drawmode = GL_TRIANGLES);
};



#endif