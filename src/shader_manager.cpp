#include "core_minimal.h"
#include "shader_manager.h"
#include "shader.h"
#include "logger.h"

namespace gn
{
  std::map<std::string, Shader*> ShaderManager::m_shaders = std::map<std::string, Shader*>();
  
  const std::map<std::string, Shader*>& ShaderManager::get()
  {
    return m_shaders;
  }

  void ShaderManager::loadShader(
    const char* vShaderFile, 
    const char* fShaderFile, 
    const char* gShaderFile, 
    const std::string& name)
  {
    Shader* shader = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    m_shaders.insert({name, shader});
  }

  Shader* ShaderManager::getShader(const std::string& name) const
  {
    return m_shaders.at(name);
  }

  Shader* ShaderManager::loadShaderFromFile(
    const char* vShaderFile, 
    const char* fShaderFile, 
    const char* gShaderFile)
  {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
      // open files
      std::ifstream vertexShaderFile(vShaderFile);
      std::ifstream fragmentShaderFile(fShaderFile);
      std::stringstream vShaderStream, fShaderStream;
      // read file's buffer contents into streams
      vShaderStream << vertexShaderFile.rdbuf();
      fShaderStream << fragmentShaderFile.rdbuf();
      // close file handlers
      vertexShaderFile.close();
      fragmentShaderFile.close();
      // convert stream into string
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
      // if geometry shader path is present, also load a geometry shader
      if (gShaderFile != nullptr)
      {
        std::ifstream geometryShaderFile(gShaderFile);
        std::stringstream gShaderStream;
        gShaderStream << geometryShaderFile.rdbuf();
        geometryShaderFile.close();
        geometryCode = gShaderStream.str();
      }
    }
    catch (std::exception e)
    {
      LOG_ERROR("ERROR::SHADER: Failed to read shader files");
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    // 2. now create shader object from source code
    Shader* shader = new Shader;
    shader->compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
  }

  void ShaderManager::free()
  {
    for(auto it = m_shaders.begin(); it != m_shaders.end(); ++it)
      delete it->second;
    m_shaders.clear();
  }

}