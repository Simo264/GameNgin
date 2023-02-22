#include "core_minimal.h"
#include "world.h"
#include "shader.h"
#include "box.h"

#include "subsystems/texture_manager.h"
#include "subsystems/file_manager.h"

extern gn::TextureManager gTextures;  

namespace gn
{
  std::map<uint32_t, Object*> World::m_worldObjects = std::map<uint32_t, Object*>();

  const std::map<uint32_t, Object*>& World::getWorldObjects()
  {
    return m_worldObjects;
  }

  Object* World::getObjectByName(const char* objectname)
  {
    for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); ++it)
    {
      Object* obj = it->second;
      if(obj->name.compare(objectname) == 0)
        return obj;
    }
    return nullptr;
  }

  Object* World::getObjectByID(uint32_t objectid)
  {
    auto it = m_worldObjects.find(objectid);
    if (it == m_worldObjects.end())
      return nullptr;
    return it->second;
  }

  void World::pushObject(Object* object)
  {
    if(!object) return;

    m_worldObjects.insert({object->id, object});
  }

  void World::destroyObject(Object* object)
  {
    if(!object) return;

    m_worldObjects.erase(object->id);
    delete object;
  }

  void World::destroyObject(uint32_t objectid)
  {
    Object* obj = getObjectByID(objectid);
    if(!obj) return;

    m_worldObjects.erase(objectid);
    delete obj;
  }

  void World::init()
  {
    std::vector<std::string> buffer;
    FileManager::read(WORLD_INI_FILE, buffer);
    
    uint32_t    objid = 0;
    float       objrotation;
    vec2        objsize;
    vec2        objpos;
    vec2        objscaling;
    color8_t    objcolor;
    std::array<char, 50> objname;
    std::array<char, 50> objtexture;

    std::array<char, 20> key;
    std::array<char, 20> value;

    for(auto it = buffer.begin(); it != buffer.end(); ++it)
    {
      if(it->empty()) continue;

      objname.fill(0);
      objtexture.fill(0);

      std::copy_n(it->begin() + 1, it->size() - 2, objname.begin());

      for(int i = 0; i < 6; i++)
      {
        key.fill(0);
        value.fill(0);

        ++it;

        int delimiter = it->find("=");
        
        std::copy_n(it->begin(), delimiter, key.begin());
        std::copy(it->begin() + delimiter + 1, it->end(), value.begin()); 

        if(strcmp(key.data(), "rotation") == 0)
        {
          objrotation = std::stof(value.data());
          continue;
        }
        if(strcmp(key.data(), "size") == 0)
        {
          char* split = strtok(value.data(), ",");
          int x = std::stoi(split);
          split = strtok(NULL, ",");
          int y = std::stoi(split);

          objsize = vec2{ x,y };
          continue;
        }
        if(strcmp(key.data(), "scaling") == 0)
        {
          char* split = strtok(value.data(), ",");
          int x = std::stoi(split);
          split = strtok(NULL, ",");
          int y = std::stoi(split);

          objscaling = vec2{ x,y };
          continue;
        }
        if(strcmp(key.data(), "position") == 0)
        {
          char* split = strtok(value.data(), ",");
          int x = std::stoi(split);
          split = strtok(NULL, ",");
          int y = std::stoi(split);
          
          objpos = vec2{ x,y };
          continue;
        }
        if(strcmp(key.data(), "texture") == 0)
        {
          std::copy(value.begin(), value.end(), objtexture.begin());
          continue;
        }        
        if(strcmp(key.data(), "color") == 0)
        {
          char* split = strtok(value.data(), ",");
          uint8_t r = (uint8_t) std::stoi(split);
          split = strtok(NULL, ",");
          uint8_t g = (uint8_t) std::stoi(split);
          split = strtok(NULL, ",");
          uint8_t b = (uint8_t) std::stoi(split);

          objcolor = color8_t{ r,g,b };
          continue;
        }       
      }
      pushObject(new Box(
        objid++, 
        objname.data(), 
        objsize, 
        objpos, 
        objcolor, 
        gTextures.getTexture(objtexture.data()), 
        objrotation, 
        objscaling));

    }
  }

  void World::render(Shader* shader)
  {
    for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); ++it)
      it->second->render(shader);
  }

  void World::free()
  {
    for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); it++)
      delete (it->second);
    m_worldObjects.clear();
  }

}


