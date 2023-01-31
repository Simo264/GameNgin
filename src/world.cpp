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

  Object* get_object_by_id(uint32_t objectid)
  {
    auto it = world_objects.find(objectid);
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

  void destroy_object(uint32_t objectid)
  {
    Object* obj = get_object_by_id(objectid);
    if(!obj) return;

    world_objects.erase(objectid);
    delete obj;
  }

  void push_object(Object* object)
  {
    if(!object) return;

    world::world_objects.insert({object->id, object});
  }

  void render(Shader* shader)
  {
    for(auto it = world_objects.begin(); it != world_objects.end(); ++it)
    {
      Object* obj = it->second;
      obj->render(shader);
    }
  }

  void free()
  {
    for(auto it = world_objects.begin(); it != world_objects.end(); it++)
      delete (it->second);
  }

}


