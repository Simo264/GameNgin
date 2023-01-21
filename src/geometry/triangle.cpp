#include "triangle.h"
#include "../shader.h"


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

void Triangle::render(Shader* shader)
{
  shader->use();
  m_vaOBJ.get()->bind();
  glDrawArrays(GL_TRIANGLES, 0, 3);
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