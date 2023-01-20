#include "vertex_array.h"
#include "vertex_buffer.h"

#include <GL/glew.h>

VertexArray::VertexArray()
{
  glGenVertexArrays(1, &m_vaOBJ);
  bind();
}

void VertexArray::setAttribFormat(
  uint32_t  attribindex, 
  uint32_t  size, 
  uint32_t  type, 
  bool      normalized, 
  uint32_t  offset)
{
  glVertexAttribFormat(attribindex, size, type, normalized, offset);
}

void VertexArray::setAttribBinding(uint32_t attribindex, uint32_t bindingindex)
{
  glVertexArrayAttribBinding(m_vaOBJ, attribindex, bindingindex);
}

void VertexArray::bindVertexBuffer(
  uint32_t      bindingindex,
  VertexBuffer* buffer,
  uint32_t      offset,
  uint32_t      stride)
{
  glVertexArrayVertexBuffer(m_vaOBJ, bindingindex, buffer->getBufferOBJ(), offset, stride);
}