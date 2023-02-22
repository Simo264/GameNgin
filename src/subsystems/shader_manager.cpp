#include "../core_minimal.h"

#include "shader_manager.h"
#include "file_manager.h"

#include "../shader.h"

namespace gn
{
  std::map<std::string, Shader*> ShaderManager::m_shaders = std::map<std::string, Shader*>();

  void ShaderManager::loadShader(
    const std::string& vShaderFilePath, 
    const std::string& fShaderFilePath, 
    const std::string& name)
  {
    std::string vsSource, fsSource;     
    FileManager::read(vShaderFilePath, vsSource);
    FileManager::read(fShaderFilePath, fsSource);

    // 2. compile shaders
    std::unique_ptr<Shader> shader = std::unique_ptr<Shader>(new Shader);
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

  const std::map<std::string, Shader*>& ShaderManager::get()
  {
    return m_shaders;
  }

  Shader* ShaderManager::getShader(const std::string& name) const
  {
    return m_shaders.at(name);
  }


  void ShaderManager::init()
  {
    std::vector<std::string> buffer;
    FileManager::read(SHADERS_INI_FILE, buffer);

    std::array<char, 50>  shadername;
    std::array<char, 100> vertexshaderPath;
    std::array<char, 100> fragshaderPath;

    std::array<char, 20> key;
    std::array<char, 50> value;
    
    for(auto it = buffer.begin(); it != buffer.end(); ++it)
    {
      if(it->empty()) continue;

      shadername.fill(0);
      vertexshaderPath.fill(0);
      fragshaderPath.fill(0);

      std::copy_n(it->begin() + 1, it->size() - 2, shadername.begin());
      
      for(int i = 0; i < 2; i++)
      {
        key.fill(0);
        value.fill(0);

        ++it;

        const int& delimiter = it->find("=");
        
        std::copy_n(it->begin(), delimiter, key.begin());
        std::copy(it->begin() + delimiter + 1, it->end(), value.begin()); 

        if(strcmp(key.data(), "vertex")  == 0)
          std::copy(value.begin(), value.end(), vertexshaderPath.begin());

        else if(strcmp(key.data(), "fragment") == 0)
          std::copy(value.begin(), value.end(), fragshaderPath.begin());
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