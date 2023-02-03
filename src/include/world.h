#ifndef WORLD_H
#define WORLD_H

#include "object.h"


namespace gn
{
  // World class
  // -----------------------------------------------------------
  class World
  {
    private:
      static std::map<uint32_t, Object*> m_worldObjects;

    public:
      World() = default;
      ~World() = default;

      static const std::map<uint32_t, Object*>& getWorldObjects();

      Object* getObjectByName(const char* objectname);
      Object* getObjectByID(uint32_t objectid);

      void pushObject(Object* object);

      void destroyObject(Object* object);
      void destroyObject(uint32_t objectid);

      void free();
  };
  // -----------------------------------------------------------

};
#endif