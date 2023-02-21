#ifndef WORLD_H
#define WORLD_H

namespace gn
{
  // World class
  // -----------------------------------------------------------
  class World
  {
    private:
      static std::map<uint32_t, class Object*> m_worldObjects;

    public:
      World() = default;
      ~World() = default;

      static const std::map<uint32_t, class Object*>& getWorldObjects();

      class Object* getObjectByName(const char* objectname);
      class Object* getObjectByID(uint32_t objectid);

      void pushObject(class Object* object);

      void destroyObject(class Object* object);
      void destroyObject(uint32_t objectid);

      void init();
      void render(class Shader*);
      void free();
  };
  // -----------------------------------------------------------

};
#endif