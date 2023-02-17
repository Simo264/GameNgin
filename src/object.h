#ifndef OBJECT_H
#define OBJECT_H

namespace gn
{
  // Object class 
  // -----------------------------------------------------------
  class Object
  {
  public:
    uint32_t    id;
    std::string name;

    Object(uint32_t objectid, std::string objectname) : id{objectid}, name{objectname} { }
    
    virtual ~Object() = default;

    virtual std::string toString() { return std::to_string(id) + std::string(". " + name); }

    virtual void render(class Shader* shader) { }
  }; 
  // -----------------------------------------------------------

}
#endif