#include "../core_minimal.h"

#include "shader_manager.h"
#include "file_manager.h"

#include "../shader.h"
#include "../logger.h"

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
    std::string buffer;
    FileManager::read(SHADERS_INI_FILE, buffer);

    std::vector<std::string> lines;
    lines.reserve(std::count(buffer.begin(), buffer.end(), '\n'));

    std::string linebuffer;
    linebuffer.reserve(100);
    for(char c : buffer)
    {
      if(c == '\n')
      {
        if(!linebuffer.empty())
          lines.push_back(linebuffer);
        linebuffer.erase(0, 100);
      }
      else
        linebuffer.push_back(c);
    }

    std::string shadername;
    std::string vertexshaderPath;
    std::string fragshaderPath;
    shadername.reserve(50);
    vertexshaderPath.reserve(100);
    fragshaderPath.reserve(100);

    int nline = 0;
    for(std::string& line : lines)
    {
      const int linesize = line.size();
      if(line.at(0) == '[' && line.at(linesize - 1) == ']')
      {
        nline = 0;
      }

      if(nline == 0)
      {
        shadername = line.substr(1, linesize - 2);
      }
      else if(nline == 1)
      {
        vertexshaderPath = line;
      }
      else if(nline == 2)
      {
        fragshaderPath = line;
        loadShader(vertexshaderPath, fragshaderPath, shadername);
      }

      nline++;
    }
  
  }

  void ShaderManager::free()
  {
    for(auto it = m_shaders.begin(); it != m_shaders.end(); ++it)
      delete it->second;
    m_shaders.clear();
  }

}