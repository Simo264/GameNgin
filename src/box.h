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
    float             angle = 0.f;
    vec2              size;  
    vec2              scaling = { 1,1 };
    vec2              position;
    class Texture*    texture; 
    transform_t       transform;
    
    Box(
      uint32_t        objectid, 
      std::string     objectname, 
      vec2            size, 
      vec2            pos, 
      class Texture*  texture = nullptr);

    // void scale(float x, float y) { transform.scale = glm::scale(transform.scale, vec3(x, y, 0.f)); }
    
    const mat4 getModel() const { 
      return  
        glm::translate(transform.translate, vec3(position, 0.f)) * 
        glm::scale(transform.scale, vec3(size.x*scaling.x, size.y*scaling.y, 0.f)) * 
        glm::rotate(transform.rotate, radians(angle), vec3(0.f, 0.f, 1.f)); }

    void setColor(color8_t color);

    void render(class Shader* shader) override;
  };
  // -----------------------------------------------------------

}

#endif