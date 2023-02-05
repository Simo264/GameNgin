#include "core_minimal.h"
#include "world.h"

namespace gn
{
  std::map<uint32_t, ObjectGL*> World::m_worldObjects = std::map<uint32_t, ObjectGL*>();

  const std::map<uint32_t, ObjectGL*>& World::getWorldObjects()
  {
    return m_worldObjects;
  }

  ObjectGL* World::getObjectByName(const char* objectname)
  {
    for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); ++it)
    {
      ObjectGL* obj = it->second;
      if(obj->name.compare(objectname) == 0)
        return obj;
    }
    return nullptr;
  }

  ObjectGL* World::getObjectByID(uint32_t objectid)
  {
    auto it = m_worldObjects.find(objectid);
    if (it == m_worldObjects.end())
      return nullptr;
    return it->second;
  }

  void World::pushObject(ObjectGL* object)
  {
    if(!object) return;

    m_worldObjects.insert({object->id, object});
  }

  void World::destroyObject(ObjectGL* object)
  {
    if(!object) return;

    m_worldObjects.erase(object->id);
    delete object;
  }

  void World::destroyObject(uint32_t objectid)
  {
    ObjectGL* obj = getObjectByID(objectid);
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


