#include "core_minimal.h"
#include "shader_manager.h"
#include "shader.h"
#include "logger.h"

namespace gn
{
  std::map<std::string, Shader*> ShaderManager::m_shaders = std::map<std::string, Shader*>();

  void ShaderManager::loadShader(
    const std::string& vShaderFilePath, 
    const std::string& fShaderFilePath, 
    const std::string& name)
  {

    std::ifstream vShaderFile, fShaderFile;
		vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
		try 
		{
			std::string vsSource, fsSource;
			std::stringstream vShaderStream, fShaderStream, gShaderStream;

			vShaderFile.open(vShaderFilePath.c_str());		// open file
			vShaderStream << vShaderFile.rdbuf();	// read file's buffer contents into streams
			vShaderFile.close();									// close file
			vsSource = vShaderStream.str();				// convert stream into string 

			fShaderFile.open(fShaderFilePath.c_str());		// open file
			fShaderStream << fShaderFile.rdbuf(); // read file's buffer contents into streams
			fShaderFile.close();									// close file
			fsSource = fShaderStream.str();				// convert stream into string 

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
		catch (std::ifstream::failure& e)
		{
			LOG_ERROR(std::string("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: ") + std::string(e.what()));
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

  void ShaderManager::free()
  {
    for(auto it = m_shaders.begin(); it != m_shaders.end(); ++it)
      delete it->second;
    m_shaders.clear();
  }

}