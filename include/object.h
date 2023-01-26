#ifndef OBJECT_H
#define OBJECT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <string>

#include "vertex_array.h"
#include "vertex.h"

// abstract class Object
// -----------------------------------------------------------
class Object
{
private:
  static uint32_t m_instancecounter;
  uint32_t        m_id;
  std::string     m_name;

protected:
  std::unique_ptr<VertexArray>                     m_vaOBJ; // vertex array
  std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>         m_vbOBJ; // vertex buffer
  std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ; // index buffer [ optional ]

  /* rotation matrix */
  glm::mat4 m_rotatemat  = glm::mat4(1.f);

public:
  /* object id readonly */
  const uint32_t& id = m_id;
  /* object name readonly */
  const std::string& name = m_name;
  /* object dimension */
  glm::vec2 dimension;
  /* object dimension */
  glm::vec2 position;

  Object(glm::vec2 dimension_, glm::vec2 position_) 
    : dimension{dimension_}, position{position_} 
  {
    m_id = m_instancecounter;
    m_instancecounter++;
    m_name = std::string("Object_") + std::to_string(id);
  }

  ~Object()  = default;

  void rotate(float angle)
  {
    m_rotatemat = glm::rotate(m_rotatemat, glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));
  }

  const std::string toString() const 
  {
    return "id=" + std::to_string(id) + " name=" + name;
  }

  virtual void render(class Shader*, uint32_t drawmode) = 0;
};
// -----------------------------------------------------------

#endif