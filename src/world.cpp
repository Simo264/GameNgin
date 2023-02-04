#include "core_minimal.h"
#include "world.h"

namespace gn
{
  std::map<uint32_t, Object*> World::m_worldObjects = std::map<uint32_t, Object*>();

  const std::map<uint32_t, Object*>& World::getWorldObjects()
  {
    return m_worldObjects;
  }

  Object* World::getObjectByName(const char* objectname)
  {
    for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); ++it)
    {
      Object* obj = it->second;
      if(obj->name.compare(objectname) == 0)
        return obj;
    }
    return nullptr;
  }

  Object* World::getObjectByID(uint32_t objectid)
  {
    auto it = m_worldObjects.find(objectid);
    if (it == m_worldObjects.end())
      return nullptr;
    return it->second;
  }

  void World::pushObject(Object* object)
  {
    if(!object) return;

    m_worldObjects.insert({object->id, object});
  }

  void World::destroyObject(Object* object)
  {
    if(!object) return;

    m_worldObjects.erase(object->id);
    delete object;
  }

  void World::destroyObject(uint32_t objectid)
  {
    Object* obj = getObjectByID(objectid);
    if(!obj) return;

    m_worldObjects.erase(objectid);
    delete obj;
  }

  void World::free()
  {
    for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); it++)
      delete (it->second);
    m_worldObjects.clear();
  }

}


