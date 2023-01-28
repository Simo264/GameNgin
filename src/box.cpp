#include "../include/core_minimal.h"

#include "../include/box.h"
#include "../include/shader.h"
#include "../include/globals.h"

/* default vertex positions */
const std::array<position_t, 4> Box::m_localspace = {
  position_t{ -1, -1 }, // bottom left
  position_t{ +1, -1 }, // bottom right
  position_t{ -1, +1 }, // top left
  position_t{ +1, +1 }  // top right
};
/* default vertex indices */
const std::array<uint8_t, 6> Box::m_indices = {
  0,1,3,  // tl - tr -  bl
  0,2,3   // tl - bl - br
};


Box::Box(glm::vec2 dimension_, glm::vec2 position_) 
: Object(), dimension{dimension_}, position{position_}
{
  name = "Box_" + std::to_string(id);

  /* default color values */
  m_colors = {
    color8_t{ 255, 0, 0 },      // top left
    color8_t{ 0, 255, 0 },      // top right
    color8_t{ 0, 0, 255 },      // bottom left
    color8_t{ 255, 255, 255 },  // bottom right
  };

  init();
}

void Box::init()
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

void Box::render(Shader* shader, uint32_t drawmode)
{
  const glm::mat4 scale       = glm::scale(glm::mat4(1.f), glm::vec3(
    dimension*0.5f, 0.f));
  
  const glm::mat4 translate   = glm::translate(glm::mat4(1.f), glm::vec3(
    position.x + dimension.x/2,
    position.y + dimension.y/2, 
    0.f));
  
  const glm::mat4 model       = translate * m_rotatemat * scale;
  const glm::mat4 projection  = glm::ortho(0.f, (float)globals::window_width, (float)globals::window_height, 0.f, -1.0f, 1.0f);

  shader->use();
  shader->setMatrix4("model", model);
  shader->setMatrix4("projection", projection);
  
  m_vaOBJ.get()->bind();
  glDrawElements(drawmode, 6, GL_UNSIGNED_BYTE, 0);
}

void Box::setColors(std::array<color8_t, 4> colors)
{
  m_colors = colors;

  m_vbOBJ.get()->namedBufferSubData(
    sizeof(m_localspace),
    sizeof(m_colors),
    m_colors.data());

}
