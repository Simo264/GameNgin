#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "object.h"
#include "vertex.h"
#include "transform.h"

namespace gn
{
  // Box class
  // -----------------------------------------------------------
  class Box : public Object
  {
  private:
    void init();

  public:
    vec2              size;  
    vec2              position;   
    class Texture*    texture; 
    transform_t       transform;
    
    Box(
      uint32_t        objectid, 
      std::string     objectname, 
      vec2            size, 
      vec2            pos, 
      class Texture*  texture = nullptr);

    void rotate(float angle)    { transform.rotate    = glm::rotate(transform.rotate, radians(angle), vec3(0.f, 0.f, 1.f)); }
    void scale(vec2 size)       { transform.scale     = glm::scale(transform.scale, vec3(size, 0.f)); }
    void translate(vec2 pos)    { transform.translate = glm::translate(transform.translate, vec3(pos, 0.f)); }
    const mat4 getModel() const { return transform.translate * transform.rotate * transform.scale; }

    void setColor(color8_t color);

    void render(class Shader* shader) override;
  };
  // -----------------------------------------------------------

}

#endif