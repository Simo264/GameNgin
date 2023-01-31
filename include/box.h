#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "object.h"
#include "vertex.h"
#include "vertex_array.h"

// Box class
// -----------------------------------------------------------
class Box : public Object
{
private:
  /* buffers */
  std::unique_ptr<VertexArray>                     m_vaOBJ;
  std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>         m_vbOBJ;
  std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ; 
  
  /* default vertex positions */
  static const std::array<position_t, 4>  m_localspace;
  /* default vertex indices */
  static const std::array<uint8_t,    6>  m_indices;
  
  /* vertex colors */
  std::array<color8_t, 4>  m_colors;

  /* rotation matrix */
  glm::mat4 m_rotatemat  = glm::mat4(1.f);

  void init();

public:
  /* object dimension */
  glm::vec2 dimension;
  /* object dimension */
  glm::vec2 position;
  /* object drawmode */
  uint32_t drawmode = GL_TRIANGLES;

  Box(glm::vec2 dimension_, glm::vec2 position_);

  void rotate(float angle)
  {
    m_rotatemat = glm::rotate(m_rotatemat, glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));
  }

  void render(class Shader* shader) override;

  void setColors(std::array<color8_t, 4> colors);
};

#endif