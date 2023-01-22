#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <GL/glew.h>

#include "buffer.h"

// Window class
// -----------------------------------------------------------
class VertexArray
{
private:
  uint32_t m_vaOBJ;

public:
  VertexArray();
  ~VertexArray() { glDeleteVertexArrays(1, &m_vaOBJ); }

  // specify the organization of vertex arrays
  // -----------------------------------------
  void setAttribFormat(
    uint32_t  attribindex, 
    uint32_t  size, 
    uint32_t  type, 
    bool      normalized, 
    uint32_t  offset);

  // associate a vertex attribute and a vertex buffer binding for a vertex array object
  // ---------------------------------------------------------------------------------- 
  void setAttribBinding(
    uint32_t attribindex,
 	  uint32_t bindingindex);

  // bind a buffer to a vertex buffer bind point
  // -------------------------------------------
  void bindVertexBuffer(
 	  uint32_t  bindingindex,
 	  Buffer<GL_ARRAY_BUFFER>* buffer,
 	  uint32_t  offset,
 	  uint32_t  stride);

  // Enable or disable a generic vertex attribute array
  // -------------------------------------------------- 
  void enableAttribute(uint32_t index)  { glEnableVertexAttribArray(index);   }
  void disableAttribute(uint32_t index) { glDisableVertexAttribArray(index);  }

  void bind()   const { glBindVertexArray(m_vaOBJ); }
  void unbind() const { glBindVertexArray(0);       }
};
// -----------------------------------------------------------

#endif