#ifndef OBJECT_H
#define OBJECT_H

#include "vertex_array.h"

// Object class 
// -----------------------------------------------------------
namespace gn
{
  class Object
  {
  protected:
    // buffers
    std::unique_ptr<VertexArray>                     m_vaOBJ; // vertex array
    std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>         m_vbOBJ; // vertex buffer
    std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ; // index buffer [optional]

  public:
    uint32_t    id;
    std::string name;

    Object(uint32_t objectid, std::string objectname) : id{objectid}, name{objectname} { }
    
    virtual ~Object() = default;

    virtual std::string toString() { return std::to_string(id) + name; }

    virtual void render(class Shader* shader) { }
  }; 
  // -----------------------------------------------------------

}
#endif