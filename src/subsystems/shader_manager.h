#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

namespace gn
{
  class ShaderManager
  {
  private:
    static std::map<std::string, class Shader*>  m_shaders;

  public:
    ShaderManager() = default;
    ~ShaderManager() = default;

    static const std::map<std::string, class Shader*>& get();

    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. 
    // If gShaderFile is not nullptr, it also loads a geometry shader
    void loadShader(
      const std::string& vShaderFilePath, 
      const std::string& fShaderFilePath, 
      const std::string& name);

    // retrieves a stored sader
    class Shader* getShader(const std::string& name) const;

    // load all shaders
    void init();
    
    // properly de-allocates all loaded resources
    void free();
  };
  
}

#endif