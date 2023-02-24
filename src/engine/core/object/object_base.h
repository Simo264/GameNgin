#ifndef OBJECT_BASE_H
#define OBJECT_BASE_H

namespace gn
{
  // Object base class 
  // -----------------------------------------------------------
  class ObjectBase
  {
  protected:
    uint32_t  m_id;
    string    m_name;

  public:
    ObjectBase(uint32_t objectid, const string& objectname) 
      : m_id{objectid}, m_name{objectname} { }
    
    virtual ~ObjectBase() = default;

    // object name
    // ---------------
    void getName(string& destname)
    {
      destname.reserve(m_name.size() + 1);
      copy(m_name.begin(), m_name.end(), destname.begin());
    }
    const string& getName() const { return m_name; }

    // object ID
    // ---------------
    const uint32_t& getID() const { return m_id; }
  }; 
  // -----------------------------------------------------------

}
#endif