#include "include/core_minimal.h"
#include "include/world.h"

namespace World
{
  std::map<uint32_t, Object*> world_objects;


  Object* getObjectByName(const char* objectname)
  {
    for(auto it = world_objects.begin(); it != world_objects.end(); ++it)
    {
      Object* obj = it->second;
      if(obj->name.compare(objectname) == 0)
        return obj;
    }
    return nullptr;
  }

  Object* getObjectByID(uint32_t objectid)
  {
    auto it = world_objects.find(objectid);
    if (it == world_objects.end())
      return nullptr;
    return it->second;
  }

  void pushObject(Object* object)
  {
    if(!object) return;

    world_objects.insert({object->id, object});
  }

  void destroyObject(Object* object)
  {
    if(!object) return;

    world_objects.erase(object->id);
    delete object;
  }

  void destroyObject(uint32_t objectid)
  {
    Object* obj = getObjectByID(objectid);
    if(!obj) return;

    world_objects.erase(objectid);
    delete obj;
  }

  void free()
  {
    for(auto it = world_objects.begin(); it != world_objects.end(); it++)
      delete (it->second);
  }

}


