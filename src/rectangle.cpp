#include "../include/rectangle.h"
#include "../include/shader.h"
#include "../include/globals.h"

#include <glm/gtc/matrix_transform.hpp>

/* default vertex positions */
const std::array<position_t, 4> Rectangle::m_localspace = {
  position_t{ -1, -1 }, // bottom left
  position_t{ +1, -1 }, // bottom right
  position_t{ -1, +1 }, // top left
  position_t{ +1, +1 }  // top right
};
/* vertex indices */
const std::array<uint8_t, 6> Rectangle::m_indices = {
  0,1,3,  // tl - tr -  bl
  0,2,3   // tl - bl - br
};


Rectangle::Rectangle(glm::vec2 dimension_, glm::vec2 position_) 
: Object(dimension_, position_)
{
  /* default color values */
  m_colors = {
    color8_t{ 255, 0, 0 },      // top left
    color8_t{ 0, 255, 0 },      // top right
    color8_t{ 0, 0, 255 },      // bottom left
    color8_t{ 255, 255, 255 },  // bottom right
  };

  init();
}

void Rectangle::init()
{
  /* create vertex array */
  m_vaOBJ = std::unique_ptr<VertexArray>(new VertexArray);
  
  /* create vertex buffer */
  m_vbOBJ = std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>(
    new Buffer<GL_ARRAY_BUFFER>(sizeof(m_localspace) + sizeof(m_colors)));
  
  /* create and init index buffer */
  m_ibOBJ = std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>>(
    new Buffer<GL_ELEMENT_ARRAY_BUFFER>(sizeof(m_indices), m_indices.data()));

  /* init vertex buffer */
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

void Rectangle::render(Shader* shader, uint32_t drawmode)
{
  m_vaOBJ.get()->bind();
  
  const glm::mat4 scale       = glm::scale(glm::mat4(1.f), glm::vec3(dimension, 0.f));
  const glm::mat4 translate   = glm::translate(glm::mat4(1.f), glm::vec3(position, 0.f));
  const glm::mat4 model       = translate * m_rotatemat * scale;
  const glm::mat4 projection  = glm::ortho(0.f, 720.f, 720.f, 0.f, -1.0f, 1.0f);

  shader->use();
  shader->setMatrix4("model", model);
  shader->setMatrix4("projection", projection);

  glDrawElements(drawmode, 6, GL_UNSIGNED_BYTE, 0);
}

void Rectangle::setColors(std::array<color8_t, 4> colors)
{
  m_colors = colors;

  m_vbOBJ.get()->namedBufferSubData(
    sizeof(m_localspace),
    sizeof(m_colors),
    m_colors.data());

}
