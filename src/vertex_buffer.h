#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <GL/glew.h>

// VertexBuffer class
// -----------------------------------------------------------
class VertexBuffer
{
private:
  uint32_t m_bufferOBJ;
  uint32_t m_usage;

public:
  VertexBuffer(
    uint32_t    size, 
    const void* data = nullptr, 
    uint32_t    usage = GL_STATIC_DRAW);
  
  ~VertexBuffer()     { glDeleteBuffers(1, &m_bufferOBJ); }

  void namedBufferData(uint32_t size, const void* data)
  {
    glNamedBufferData(m_bufferOBJ, size, data, m_usage);
  }
  void namedBufferSubData(uint32_t offset, uint32_t size, const void* data)
  {
    glNamedBufferSubData(m_bufferOBJ, offset, size, data);
  }

  void bind()   const { glBindBuffer(GL_ARRAY_BUFFER, m_bufferOBJ);   }
  void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0);             }

  uint32_t getBufferOBJ() const { return m_bufferOBJ; }
};
// -----------------------------------------------------------

#endif