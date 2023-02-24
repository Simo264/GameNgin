#include "engine/core/core.h"

#include "shader_manager.h"
#include "file_manager.h"

#include "engine/core/shader/shader.h"
#include "engine/core/IO/logger.h"

namespace gn
{
  void ShaderManager::loadShader(
    const string& vShaderFilePath, 
    const string& fShaderFilePath, 
    const string& name)
  {
    string vsSource, fsSource;     
    FileManager::read(vShaderFilePath, vsSource);
    FileManager::read(fShaderFilePath, fsSource);

    // 2. compile shaders
    unique_ptr<Shader> shader = unique_ptr<Shader>(new Shader);
    bool compiled = shader.get()->compile(vsSource.c_str(), fsSource.c_str());
    if(!compiled)
    {
      LOG_ERROR("Error on compile shader");
      shader.reset();
    }
    else
    {
      m_shaders.insert({name, shader.release()});
    }
  }


  Shader* ShaderManager::getShader(const string& name) const
  {
    return m_shaders.at(name);
  }

  void ShaderManager::init()
  {
    vector<string> buffer;
    FileManager::read(SHADERS_INI_FILE, buffer);

    array<char, 50>  shadername;
    array<char, 100> vertexshaderPath;
    array<char, 100> fragshaderPath;

    array<char, 20> key;
    array<char, 50> value;
    
    for(auto it = buffer.begin(); it != buffer.end(); ++it)
    {
      if(it->empty()) continue;

      shadername.fill(0);
      vertexshaderPath.fill(0);
      fragshaderPath.fill(0);

      copy_n(it->begin() + 1, it->size() - 2, shadername.begin());
      
      for(int i = 0; i < 2; i++)
      {
        key.fill(0);
        value.fill(0);

        ++it;

        const int& delimiter = it->find("=");
        
        copy_n(it->begin(), delimiter, key.begin());
        copy(it->begin() + delimiter + 1, it->end(), value.begin()); 

        if(strcmp(key.data(), "vertex")  == 0)
          copy(value.begin(), value.end(), vertexshaderPath.begin());

        else if(strcmp(key.data(), "fragment") == 0)
          copy(value.begin(), value.end(), fragshaderPath.begin());
      }
      loadShader(vertexshaderPath.data(), fragshaderPath.data(), shadername.data());
    }
  }

  void ShaderManager::free()
  {
    for(auto it = m_shaders.begin(); it != m_shaders.end(); ++it)
      delete it->second;
    m_shaders.clear();
  }

}