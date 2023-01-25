#ifndef ABC_OBJECT_H
#define ABC_OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <string>

#include "../vertex_array.h"
#include "../vertex.h"

// abstract class Object
// -----------------------------------------------------------
class ABCobject
{
protected:
  std::unique_ptr<VertexArray>                     m_vaOBJ; // vertex array
  std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>         m_vbOBJ; // vertex buffer
  std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ; // index buffer [ optional ]

  /* model space */
  glm::mat4 m_rotatemat  = glm::mat4(1.f);

public:
  /* object dimension */
  glm::vec2 dimension;
  /* object dimension */
  glm::vec2 position;

  ABCobject(glm::vec2 dimension_, glm::vec2 position_) 
    : dimension{dimension_}, position{position_} { }
  ~ABCobject()  = default;

  void rotate(float angle)
  {
    m_rotatemat = glm::rotate(m_rotatemat, glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));
  }

  // const std::string getInfo() const
  // {
  //   return (
  //     "width=" + std::to_string(dimension.x) + " " + 
  //     "height=" + std::to_string(dimension.y));
  // }

  virtual void render(class Shader*, uint32_t drawmode) = 0;
};
// -----------------------------------------------------------


#endif