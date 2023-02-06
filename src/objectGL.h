#ifndef OBJECT_H
#define OBJECT_H

#include "vertex.h"
#include "vertex_array.h"
#include "transform.h"

// Object class 
// -----------------------------------------------------------
namespace gn
{
  class ObjectGL
  {
  protected:
    // buffers
    std::unique_ptr<VertexArray>                     m_vaOBJ; // vertex array
    std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>         m_vbOBJ; // vertex buffer
    std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ; // index buffer [optional]

  public:
    uint32_t    id;
    std::string name;
    transform_t transform;
    uint32_t    drawmode = GL_TRIANGLES; 

    ObjectGL(uint32_t objectid, std::string objectname) 
      : id{objectid}, name{objectname} { }
    
    virtual ~ObjectGL() = default;

    virtual void render(class Shader* shader) { };

    virtual std::string toString() { return std::to_string(id) + name; }

    void rotate(float angle)  { transform.rotate    = glm::rotate(transform.rotate, radians(angle), vec3(0.f, 0.f, 1.f)); }
    void scale(vec2 size)     { transform.scale     = glm::scale(transform.scale, vec3(size, 0.f)); }
    void translate(vec2 pos)  { transform.translate = glm::translate(transform.translate, vec3(pos, 0.f)); }
  
    const mat4 getModel() const { return transform.translate * transform.rotate * transform.scale; }
  }; 
  // -----------------------------------------------------------

}
#endif