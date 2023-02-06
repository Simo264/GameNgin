#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "objectGL.h"

namespace gn
{
  // Box class
  // -----------------------------------------------------------
  class Box : public ObjectGL
  {
  private:
    class Texture* m_texture; 
    
    void init();

  public:
    vec2 size;  
    vec2 position;   
    
    Box(
      uint32_t objectid, 
      std::string objectname, 
      vec2 size, 
      vec2 pos, 
      class Texture* texture);

    void render(class Shader* shader) override;

    void setColor(color8_t color);

    class Texture* getTexture() const { return m_texture; }
    void setTexture(class Texture* texture);
  };
  // -----------------------------------------------------------

}

#endif