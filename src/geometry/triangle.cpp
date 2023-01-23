#include "triangle.h"
#include "../shader.h"
#include "../globals.h"


/* default vertex positions */
const std::array<position_t, 3> Triangle::m_localspace = {
  position_t{ -1, -1 },
  position_t{ +1, -1 },
  position_t{  0, +1 }
};

/* default color values */
const std::array<color8_t, 3> Triangle::m_colors = {
  color8_t{ 255, 0, 0 },
  color8_t{ 0, 255, 0 },
  color8_t{ 255, 255, 0 }
};

Triangle::Triangle(glm::vec2 dimension_, glm::vec2 position_)
: ABCobject(dimension_, position_)
{
  init();

  scale(1.f, 1.f);
}


void Triangle::init()
{
  m_vaOBJ = std::unique_ptr<VertexArray>(new VertexArray);

  m_vbOBJ = std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>(
    new Buffer<GL_ARRAY_BUFFER>(sizeof(m_localspace) + sizeof(m_colors)));
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

void Triangle::render(Shader* shader, uint32_t drawmode)
{
  m_vaOBJ.get()->bind();
  shader->use();

  const glm::mat4 model       = m_transmat * m_rotatemat * m_scalemat;
  const glm::mat4 view        = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
  const glm::mat4 projection  = glm::ortho(-1, 1, -1, 1);
  const glm::mat4 MVP         = projection * view * model;
  shader->setMatrix4("MVP", MVP);

  glDrawArrays(drawmode, 0, 3);
}

void Triangle::setColors(std::array<color8_t, 3> colors)
{

}
