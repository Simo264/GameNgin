#ifndef WORLD_H
#define WORLD_H

#include "engine/core/object/object_base.h"

namespace gn
{
  // World class
  // -----------------------------------------------------------
  class World
  {
    private:
      static map<uint32_t, ObjectBase*> m_worldObjects;

    public:
      // World(uint32_t id, string name) : ObjectBase(id, name) { }
      World() = default;
      ~World() = default;

      map<uint32_t, ObjectBase*>& getObjects();

      ObjectBase* getObjectByName(const string& objectname);
      ObjectBase* getObjectByID(uint32_t objectid);

      void insertObject(ObjectBase* object);

      void destroyObject(ObjectBase* object);
      void destroyObject(uint32_t objectid);

      void init();
      // void render(class Shader*);
      void free();
  };
  // -----------------------------------------------------------

};
#endif