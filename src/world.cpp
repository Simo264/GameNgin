#include "../include/core_minimal.h"

#include "../include/world.h"
#include "../include/shader.h"


namespace world
{
  std::map<uint32_t, Object*> world_objects;


  Object* get_object_by_name(const char* objectname)
  {
    for(auto it = world_objects.begin(); it != world_objects.end(); ++it)
    {
      Object* obj = it->second;
      if(obj->name.compare(objectname) == 0)
        return obj;
    }
    return nullptr;
  }

  Object* get_object_by_id(uint32_t id)
  {
    auto it = world_objects.find(id);
    if (it == world_objects.end())
      return nullptr;
    return it->second;
  }


  void destroy_object(Object* object)
  {
    if(!object) return;

    world_objects.erase(object->id);
    delete object;
  }

  void insert_object(Object* object)
  {
    if(!object) return;

    world::world_objects.insert({object->id, object});
  }


}


