#ifndef OBJECT_INTERFACE_H
#define OBJECT_INTERFACE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>

#include "../vertex_array.h"

class ObjectInterface
{
protected:
  std::unique_ptr<VertexArray>  m_vaOBJ;
  std::unique_ptr<Buffer<GL_ARRAY_BUFFER>> m_vbOBJ;

  /* model space */
  glm::mat4 m_scalemat   = glm::mat4(1.f);
  glm::mat4 m_rotatemat  = glm::mat4(1.f);
  glm::mat4 m_transmat   = glm::mat4(1.f);

public:
  ObjectInterface()  = default;
  ~ObjectInterface() = default;

  void scale(float x, float y)
  {
    m_scalemat = glm::scale(glm::mat4(1.f), glm::vec3(x, y, 0.f));
  }
  void rotate(float angle)
  {
    m_rotatemat = glm::rotate(glm::mat4(1.f), glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));
  }
  void translate(float x, float y)
  {
    m_transmat = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0.f));
  }

  virtual void render(class Shader*, uint32_t drawmode = GL_TRIANGLES) = 0;
};

#endif