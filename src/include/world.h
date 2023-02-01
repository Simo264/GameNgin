#ifndef WORLD_H
#define WORLD_H

#include "object.h"

namespace World
{
  extern std::map<uint32_t, Object*> world_objects;

  Object* getObjectByName(const char* objectname);
  Object* getObjectByID(uint32_t objectid);

  void pushObject(Object* object);

  void destroyObject(Object* object);
  void destroyObject(uint32_t objectid);

  void free();
};

#endif