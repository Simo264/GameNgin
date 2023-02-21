#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "object.h"
#include "vertex_array.h"
#include "vertex.h"
#include "transform.h"

namespace gn
{
  // Box class
  // -----------------------------------------------------------
  class Box : public Object
  {
  private:
    // buffers
    std::unique_ptr<VertexArray>                     m_vaOBJ; // vertex array
    std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>         m_vbOBJ; // vertex buffer
    std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ; // index buffer [optional]
    
    void init();

  public:
    float             rotation;
    vec2              size;  
    vec2              scaling;
    vec2              position;
    color8_t          color;
    class Texture*    texture; 

    transform_t       transform;

    uint32_t drawmode = GL_TRIANGLES;
    
    Box(
      uint32_t        id, 
      std::string     name, 
      vec2            size, 
      vec2            pos, 
      color8_t        color     = {255,255,255},
      class Texture*  texture   = nullptr,
      float           rotation  = 0.f,
      vec2            scaling   = {1.f,1.f}
    );

    const mat4 getModel() const { 
      return  
        glm::translate(transform.translate, vec3(position, 0.f)) * 
        glm::scale(transform.scale, vec3(size.x*scaling.x, size.y*scaling.y, 0.f)) * 
        glm::rotate(transform.rotate, rotation, vec3(0.f, 0.f, 1.f)); }

    void setColor(color8_t color);

    void render(class Shader* shader) override;
  };
  // -----------------------------------------------------------

}

#endif