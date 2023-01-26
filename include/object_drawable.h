#ifndef OBJECT_DRAWABLE_H
#define OBJECT_DRAWABLE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

#include "vertex_array.h"
#include "vertex.h"

class ObjectDrawable
{
private:
  std::unique_ptr<VertexArray>                     m_vaOBJ; // vertex array
  std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>         m_vbOBJ; // vertex buffer
  std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ; // index buffer [ optional ]

  /* rotation matrix */
  glm::mat4 m_rotatemat  = glm::mat4(1.f);

public:
  /* object dimension */
  glm::vec2 dimension;
  /* object dimension */
  glm::vec2 position;

  ObjectDrawable();
  ~ObjectDrawable();

  void rotate(float angle)
  {
    m_rotatemat = glm::rotate(m_rotatemat, glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));
  }

  virtual void render() = 0;
};




#endif