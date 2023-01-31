#ifndef WORLD_H
#define WORLD_H

#include "object.h"

namespace world
{
  extern std::map<uint32_t, Object*> world_objects;

  Object* get_object_by_name(const char* objectname);
  Object* get_object_by_id(uint32_t objectid);

  void push_object (Object* object);

  void destroy_object(Object* object);
  void destroy_object(uint32_t objectid);

  void free();
};

#endif