#include "vertex_buffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer(uint32_t size, const void* data, uint32_t usage)
: m_usage{usage}
{
  glGenBuffers(1, &m_bufferOBJ);
  bind();
  namedBufferData(size, data);
}