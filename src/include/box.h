#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "object.h"
#include "vertex.h"
#include "vertex_array.h"
#include "texture.h"
#include "shader.h"


using namespace GL;

namespace gn
{
  // Box class
  // -----------------------------------------------------------
  class Box : public Object
  {
  private:
    // buffers
    std::unique_ptr<VertexArray>                     m_vaOBJ;
    std::unique_ptr<Buffer<GL_ARRAY_BUFFER>>         m_vbOBJ;
    std::unique_ptr<Buffer<GL_ELEMENT_ARRAY_BUFFER>> m_ibOBJ; 
    
    // rotation matrix
    mat4 m_rotatemat  = mat4(1.f);

    void init();

  public:
    vec2 dimension;  
    vec2 position;   
    Texture* texture;
    uint32_t  drawmode = GL_TRIANGLES; 

    Box(vec2 dimension_, vec2 position_);

    void rotate(float angle)
    {
      m_rotatemat = glm::rotate(m_rotatemat, radians(angle), vec3(0.f, 0.f, 1.f));
    }

    void render(Shader* shader);

    void setColor(color8_t color);

    void setTexture(Texture* texture) { this->texture = texture; }
  };
  // -----------------------------------------------------------

}

#endif