#include "engine/core/core.h"

#include "engine/world.h"
#include "engine/core/shader/shader.h"

#include "engine/subsystems/texture_manager.h"
#include "engine/subsystems/file_manager.h"

namespace gn
{
  map<uint32_t, Box*> World::m_worldObjects = map<uint32_t, Box*>();

  const map<uint32_t, Box*>& World::getObjects()
  {
    return m_worldObjects;
  }

  Box* World::getObjectByName(const string& objectname)
  {
    for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); ++it)
    {
      Box* obj = it->second;
      if(obj->getName() == objectname)
        return obj;
    }
    return nullptr;
  }

  Box* World::getObjectByID(uint32_t objectid)
  {
    auto it = m_worldObjects.find(objectid);
    if (it == m_worldObjects.end())
      return nullptr;
    return it->second;
  }

  void World::insertObject(Box* object)
  {
    if(!object) return;

    m_worldObjects.insert({object->getID(), object});
  }

  void World::destroyObject(Box* object)
  {
    if(!object) return;

    m_worldObjects.erase(object->getID());
    delete object;
  }

  void World::destroyObject(uint32_t objectid)
  {
    Box* obj = getObjectByID(objectid);
    if(!obj) return;

    m_worldObjects.erase(objectid);
    delete obj;
  }

  void World::init()
  {
    vector<string> buffer;
    FileManager::read(WORLD_INI_FILE, buffer);
    
    uint32_t    objid = 0;
    float       objrotation;
    vec2        objsize;
    vec2        objpos;
    vec2        objscaling;
    color8_t    objcolor;
    array<char, 50> objname;
    array<char, 50> objtexture;

    array<char, 20> key;
    array<char, 20> value;

    for(auto it = buffer.begin(); it != buffer.end(); ++it)
    {
      if(it->empty()) continue;

      objname.fill(0);
      objtexture.fill(0);

      copy_n(it->begin() + 1, it->size() - 2, objname.begin());

      for(int i = 0; i < 6; i++)
      {
        key.fill(0);
        value.fill(0);

        ++it;

        int delimiter = it->find("=");
        
        copy_n(it->begin(), delimiter, key.begin());
        copy(it->begin() + delimiter + 1, it->end(), value.begin()); 

        if(strcmp(key.data(), "rotation") == 0)
        {
          objrotation = stof(value.data());
          continue;
        }
        if(strcmp(key.data(), "size") == 0)
        {
          char* split = strtok(value.data(), ",");
          int x = stoi(split);
          split = strtok(NULL, ",");
          int y = stoi(split);

          objsize = vec2{ x,y };
          continue;
        }
        if(strcmp(key.data(), "scaling") == 0)
        {
          char* split = strtok(value.data(), ",");
          int x = stoi(split);
          split = strtok(NULL, ",");
          int y = stoi(split);

          objscaling = vec2{ x,y };
          continue;
        }
        if(strcmp(key.data(), "position") == 0)
        {
          char* split = strtok(value.data(), ",");
          int x = stoi(split);
          split = strtok(NULL, ",");
          int y = stoi(split);
          
          objpos = vec2{ x,y };
          continue;
        }
        if(strcmp(key.data(), "texture") == 0)
        {
          copy(value.begin(), value.end(), objtexture.begin());
          continue;
        }        
        if(strcmp(key.data(), "color") == 0)
        {
          char* split = strtok(value.data(), ",");
          uint8_t r = (uint8_t) stoi(split);
          split = strtok(NULL, ",");
          uint8_t g = (uint8_t) stoi(split);
          split = strtok(NULL, ",");
          uint8_t b = (uint8_t) stoi(split);

          objcolor = color8_t{ r,g,b };
          continue;
        }       
      }
      // insertObject(new Box(
      //   objid++, 
      //   objname.data(), 
      //   objsize, 
      //   objpos, 
      //   objcolor, 
      //   gTextures.getTexture(objtexture.data()), 
      //   objrotation, 
      //   objscaling));

    }
  }

  // void World::render(Shader* shader)
  // {
  //   for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); ++it)
  //    it->second->render(shader);
  // }

  void World::free()
  {
    for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); it++)
      delete (it->second);
    m_worldObjects.clear();
  }

}


