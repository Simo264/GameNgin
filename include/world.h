#ifndef WORLD_H
#define WORLD_H

#include <cstdint>
#include <map>

#include "../include/object.h"

namespace world
{
  extern double world_time;
  extern std::map<uint32_t, Object*> world_objects;
  
  Object* get_object_by_name(const char* objectname);
  Object* get_object_by_id(uint32_t id);

  void    destroy_object(Object* object);
  void    insert_object (Object* object);
};

#endif