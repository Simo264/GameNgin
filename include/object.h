#ifndef OBJECT_H
#define OBJECT_H

// Object class 
// -----------------------------------------------------------
class Object
{
protected:
  static uint32_t m_instancecounter;
  uint32_t        m_id;

public:
  // object id - readonly 
  const uint32_t& id = m_id;
  std::string name;


  Object()  
  {
    m_id = m_instancecounter;
    m_instancecounter++;
    name = "Object_" + std::to_string(id);
  }

  virtual ~Object() { }

  virtual const std::string toString() const 
  {
    return "id=" + std::to_string(id) + " name=" + name;
  }
};
// -----------------------------------------------------------

#endif