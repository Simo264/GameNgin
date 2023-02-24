#ifndef WORLD_H
#define WORLD_H

#include "engine/box.h"

namespace gn
{
  // World class
  // -----------------------------------------------------------
  class World
  {
    private:
      static map<uint32_t, Box*> m_worldObjects;

    public:
      // World(uint32_t id, string name) : ObjectBase(id, name) { }
      World() = default;
      ~World() = default;

      const map<uint32_t, Box*>& getObjects();

      Box* getObjectByName(const string& objectname);
      Box* getObjectByID(uint32_t objectid);

      void insertObject(Box* object);

      void destroyObject(Box* object);
      void destroyObject(uint32_t objectid);

      void init();
      // void render(class Shader*);
      void free();
  };
  // -----------------------------------------------------------

};
#endif