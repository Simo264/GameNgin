#include "triangle.h"
#include "../shader.h"
#include "../globals.h"

#include <glm/gtc/matrix_transform.hpp>

static const glm::mat4 identity_matrix = glm::mat4(1.f);

Triangle::Triangle()
{
  m_localspace = std::array<position_t, 3> {
    position_t{ -1, -1 },
    position_t{ +1, -1 },
    position_t{  0, +1 }
  };
  m_colors = std::array<color8_t, 3> {
    color8_t{ 255, 255, 255 },
    color8_t{ 255, 255, 255 },
    color8_t{ 255, 255, 255 }
  };

  init();
}

Triangle::Triangle(std::array<position_t, 3> localspace, std::array<color8_t, 3> colors)
: m_localspace{localspace}, m_colors{colors}
{
  init();
}

void Triangle::init()
{
  m_vaOBJ = std::unique_ptr<VertexArray>(new VertexArray);

  m_vbOBJ = std::unique_ptr<VertexBuffer>(
    new VertexBuffer(sizeof(m_localspace) + sizeof(m_colors)));
  m_vbOBJ.get()->namedBufferSubData(0, sizeof(m_localspace), m_localspace.data());
  m_vbOBJ.get()->namedBufferSubData(sizeof(m_localspace), sizeof(m_colors), m_colors.data());

  m_vaOBJ.get()->enableAttribute(0);
  m_vaOBJ.get()->enableAttribute(1);
  m_vaOBJ.get()->setAttribFormat(0, 2, GL_FLOAT, false, 0);
  m_vaOBJ.get()->setAttribFormat(1, 3, GL_UNSIGNED_BYTE, true, sizeof(m_localspace));
  m_vaOBJ.get()->setAttribBinding(0, 0);
  m_vaOBJ.get()->setAttribBinding(1, 1);
  m_vaOBJ.get()->bindVertexBuffer(0, m_vbOBJ.get(), 0, sizeof(position_t));
  m_vaOBJ.get()->bindVertexBuffer(1, m_vbOBJ.get(), 0, sizeof(color8_t));
}

void Triangle::scale(float x, float y)
{
  m_scalemat = glm::scale(identity_matrix, glm::vec3(x, y, 0.f));
}

void Triangle::rotate(float angle)
{
  m_rotatemat = glm::rotate(identity_matrix, glm::radians(angle), glm::vec3(0.f, 0.f, 1.f));
}

void Triangle::translate(float x, float y)
{
  m_transmat = glm::translate(identity_matrix, glm::vec3(x, y, 0.f));
}

void Triangle::render(Shader* shader)
{
  m_vaOBJ.get()->bind();
  shader->use();

  const glm::mat4 model       = m_transmat * m_rotatemat * m_scalemat;
  const glm::mat4 view        = glm::translate(identity_matrix, glm::vec3(0.f, 0.f, 0.f)); 
  const glm::mat4 projection  = glm::ortho(-1.f, 1.f, -1.f, 1.f, -1.f, 1.f);
  
  // const glm::mat4 projection  = glm::perspective(
  //   glm::radians(45.0f), 
  //   (float)globals::window_width/(float)globals::window_height, 
  //   0.1f, 
  //   100.0f);


  shader->setMatrix4("model", model);
  shader->setMatrix4("view", view);
  shader->setMatrix4("projection", projection);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}


