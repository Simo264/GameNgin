#include "engine/core/core.h"

#include "engine/world.h"
#include "engine/core/shader/shader.h"

#include "engine/subsystems/texture_manager.h"
#include "engine/subsystems/file_manager.h"
#include "engine/subsystems/render_manager.h"

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

  void World::save(const char* filename)
  {
    //TODO:
  }

  void World::load(const char* filename)
  {
    vector<string> buffer;
    FileManager::read(WORLD_INI_FILE, buffer);
    
    uint32_t    objid;
    float       objrotation;
    vec2        objsize;
    vec2        objpos;
    vec2        objscaling;
    color8_t    objcolor;
    string      objname;
    string      objtexture;

    string key;
    string value;
    
    objname.reserve(50);
    objtexture.reserve(50);
    key.reserve(50);
    value.reserve(50); 

    for(auto it = buffer.begin(); it != buffer.end(); ++it)
    {
      if(it->empty()) continue;

      objname = it->substr(1, it->size() - 2);
      int delimiter = objname.find_last_of("_");
      objid = stoi(objname.substr(delimiter + 1));
      
      for(int i = 0; i < 6; i++)
      {
        ++it;
        
        delimiter = it->find("=");
        key   = it->substr(0, delimiter);
        value = it->substr(delimiter + 1, it->size() - 1);

        if(strcmp(key.c_str(), "rotation") == 0)
        {
          objrotation = stof(value);
          continue;
        }
        if(strcmp(key.c_str(), "size")     == 0)
        {
          istringstream iss(value);
          string str_x;
          string str_y;
          getline(iss, str_x, ',');
          getline(iss, str_y, ',');

          objsize = vec2{ stof(str_x), stof(str_y) };
          continue;
        }
        if(strcmp(key.c_str(), "scaling")  == 0)
        {
          istringstream iss(value);
          string str_x;
          string str_y;
          getline(iss, str_x, ',');
          getline(iss, str_y, ',');

          objscaling = vec2{ stof(str_x), stof(str_y) };
          continue;
        }
        if(strcmp(key.c_str(), "position") == 0)
        {
          istringstream iss(value);
          string str_x;
          string str_y;
          getline(iss, str_x, ',');
          getline(iss, str_y, ',');

          objpos = vec2{ stof(str_x), stof(str_y) };
          continue;
        }
        if(strcmp(key.c_str(), "texture")  == 0)
        {
          objtexture = value;
          continue;
        }        
        if(strcmp(key.c_str(), "color")    == 0)
        {
          istringstream iss(value);
          string str_r;
          string str_g;
          string str_b;
          getline(iss, str_r, ',');
          getline(iss, str_g, ',');
          getline(iss, str_b, ',');

          uint8_t r = (uint8_t) stoi(str_r);
          uint8_t g = (uint8_t) stoi(str_g);
          uint8_t b = (uint8_t) stoi(str_b);

          objcolor = color8_t{ r,g,b };
          continue;
        }       
      }

      insertObject(new Box(
        objid, 
        objname, 
        objpos, 
        objsize, 
        objscaling, 
        objrotation, 
        TextureManager::getInstance().getTextureByName(objtexture)));

    }
  }

  void World::render(Shader* shader)
  {
    RenderManager& rm = RenderManager::getInstance();
    for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); ++it)
    {
      rm.draw(shader, it->second);
    }
  }

  void World::free()
  {
    for(auto it = m_worldObjects.begin(); it != m_worldObjects.end(); it++)
      delete (it->second);
    m_worldObjects.clear();
  }

}


