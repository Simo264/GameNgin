#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "engine/core/object/object_base.h"
#include "engine/core/opengl/vertex_array.h"
#include "engine/core/opengl/vertex_attributes.h"
#include "engine/core/object/transform.h"
#include "engine/texture.h"

namespace gn
{
  // Box class
  // -----------------------------------------------------------
  class Box : public ObjectBase
  {
  private:
    // buffers
    unique_ptr<VertexArray>                     m_vaOBJ; // vertex array
    unique_ptr<Buffer<GL_ARRAY_BUFFER>>         m_vbOBJ; // vertex buffer
    unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ; // index buffer 

    // default vertex positions 
    static const array<position_t,  4>  localspace;
    // default vertex indices 
    static const array<uint8_t,     6>  indices;
    // default texture coordinates 
    static const array<textcoord_t, 4>  textcoords;
    
    // default box color white   
    color8_t m_color = { 255,255,255 };

    void initBuffers();

  public:
    vec2  position;
    vec2  size;
    vec2  scaling;
    float rotation;
    Texture* texture;

    Box(
      uint32_t  id,
      string    name,
      vec2      position,
      vec2      size,
      vec2      scaling   = { 1,1 },
      float     rotation  = 0.f,
      Texture*  texture   = nullptr
    );
    ~Box() = default;

    const color8_t getColor() const { return m_color; }
    void setColor(color8_t color);

    void getTransform(transform_t& outTransform);

    VertexArray*                     getVertexArray()  const { return m_vaOBJ.get(); }
    Buffer<GL_ARRAY_BUFFER>*         getVertexBuffer() const { return m_vbOBJ.get(); }
    Buffer<GL_ELEMENT_ARRAY_BUFFER>* getIndexBuffer()  const { return m_ibOBJ.get(); }
  };
  // -----------------------------------------------------------

}

#endif