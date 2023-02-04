#include "include/core_minimal.h"
#include "include/vertex_array.h"

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
  Buffer<GL_ARRAY_BUFFER>* buffer,
  uint32_t      offset,
  uint32_t      stride)
{
  glVertexArrayVertexBuffer(m_vaOBJ, bindingindex, buffer->get(), offset, stride);
}