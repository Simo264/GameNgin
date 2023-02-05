#ifndef WORLD_H
#define WORLD_H

#include "objectGL.h"


namespace gn
{
  // World class
  // -----------------------------------------------------------
  class World
  {
    private:
      static std::map<uint32_t, ObjectGL*> m_worldObjects;

    public:
      World() = default;
      ~World() = default;

      static const std::map<uint32_t, ObjectGL*>& getWorldObjects();

      ObjectGL* getObjectByName(const char* objectname);
      ObjectGL* getObjectByID(uint32_t objectid);

      void pushObject(ObjectGL* object);

      void destroyObject(ObjectGL* object);
      void destroyObject(uint32_t objectid);

      void free();
  };
  // -----------------------------------------------------------

};
#endif