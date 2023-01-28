#ifndef BUFFER_H
#define BUFFER_H

template <uint32_t target>
class Buffer
{
private:
  uint32_t m_bufferOBJ;
  const uint32_t m_usage = GL_STATIC_DRAW;

public:
  Buffer(uint32_t size, const void* data = nullptr)
  {
    glGenBuffers(1, &m_bufferOBJ);
    bind();
    namedBufferData(size, data);
  }
  
  ~Buffer() 
  {  
    glDeleteBuffers(1, &m_bufferOBJ); 
  }

  void namedBufferData(uint32_t size, const void* data)
  {
    glNamedBufferData(m_bufferOBJ, size, data, m_usage);
  }
  
  void namedBufferSubData(uint32_t offset, uint32_t size, const void* data)
  {
    glNamedBufferSubData(m_bufferOBJ, offset, size, data);
  }

  void bind()   const { glBindBuffer(target, m_bufferOBJ); }
  void unbind() const { glBindBuffer(target, 0); }

  uint32_t getBufferOBJ() const { return m_bufferOBJ; }
};



#endif