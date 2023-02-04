#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

namespace gn
{
  class ShaderManager
  {
  private:
    static std::map<std::string, class Shader*>  m_shaders;

    // loads and generates a shader from file
    Shader* loadShaderFromFile(
      const char* vShaderFile, 
      const char* fShaderFile, 
      const char* gShaderFile = nullptr);

  public:
    ShaderManager() = default;
    ~ShaderManager() = default;

    static const std::map<std::string, class Shader*>& get();

    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. 
    // If gShaderFile is not nullptr, it also loads a geometry shader
    void loadShader(
      const char* vShaderFile, 
      const char* fShaderFile, 
      const char* gShaderFile, 
      const std::string& name);

    // retrieves a stored sader
    class Shader* getShader(const std::string& name) const;

    // properly de-allocates all loaded resources
    void free();
  };
  
}

#endif