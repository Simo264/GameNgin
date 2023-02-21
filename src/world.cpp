#include "core_minimal.h"
#include "world.h"
#include "box.h"
#include "shader.h"

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
    std::string buffer;
    FileManager::read(WORLD_INI_FILE, buffer);
    
    std::vector<std::string> bufferlines;
    bufferlines.reserve(std::count(buffer.begin(), buffer.end(), '\n'));

    std::array<char, 100> bufferline;
    int indexbl = 0;
    for(char& c : buffer)
    {
      if(c == '\n')
      {
        if(strlen(bufferline.data()) != 0)
          bufferlines.push_back(bufferline.data());
        
        bufferline.fill(0);
        indexbl = 0;
      }
      else
        bufferline[indexbl++] = c;
    }


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

    for(auto it = bufferlines.begin(); it != bufferlines.end(); ++it)
    {
      objname.fill(0);
      objtexture.fill(0);

      std::copy_n(it->begin() + 1, it->size() - 2, objname.begin());

      for(int i = 0; i < 6; i++)
      {
        ++it;

        int delimiter = it->find("=");

        key.fill(0);
        value.fill(0);
        std::copy_n(it->begin(), delimiter, key.begin());
        std::copy(it->begin() + delimiter + 1, it->end(), value.begin()); 

        if(strcmp(key.data(), "rotation") == 0)
        {
          objrotation = std::stof(value.data());
          continue;
        }
        if(strcmp(key.data(), "size") == 0)
        {
          auto match = std::find(value.begin(), value.end(), ",");
          delimiter = std::distance(value.begin(), match); 
          
          std::cout << match << " " << delimiter << "\n";

          // float x;
          // float y;

          // objsize = vec2{ 
          //   std::stof(value.substr(0, delimiter)),    
          //   std::stof(value.substr(delimiter + 1))
          // };
          continue;
        }
        if(strcmp(key.data(), "scaling") == 0)
        {
          continue;
        }
        if(strcmp(key.data(), "position") == 0)
        {
          continue;
        }
        if(strcmp(key.data(), "position") == 0)
        {
          continue;
        }
        if(strcmp(key.data(), "texture") == 0)
        {
          continue;
        }        
        if(strcmp(key.data(), "color") == 0)
        {
          continue;
        }       
      }



      // else if(line.find("size")     != std::string::npos)
      // {

      // }
      // else if(line.find("scaling")  != std::string::npos)
      // {
      //   objscaling = vec2{ 
      //     std::stof(value.substr(0, value.find(","))),    // x
      //     std::stof(value.substr(value.find(",") + 1))    // y
      //   };  
      // }
      // else if(line.find("position") != std::string::npos)
      // {
      //   objpos = vec2{ 
      //     std::stof(value.substr(0, value.find(","))),    // x
      //     std::stof(value.substr(value.find(",") + 1))    // y
      //   };  
      // }
      // else if(line.find("texture")  != std::string::npos)
      // {
      //   objtexture = value;
      // }
      // else if(line.find("color")    != std::string::npos)
      // {
      //   std::istringstream iss(value);
      //   std::string str; 
      //   str.reserve(5);
        
      //   int i = 0;
      //   while (getline(iss, str, ','))
      //     objcolor[i++] = (uint8_t) std::stoi(str);
      // }
      // else if(line.empty())
      // {
      //   pushObject(new Box(
      //     objid++, 
      //     objname, 
      //     objsize, 
      //     objpos, 
      //     objcolor, 
      //     gTextures.getTexture(objtexture), 
      //     objrotation, 
      //     objscaling));
      // }
   
   
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


