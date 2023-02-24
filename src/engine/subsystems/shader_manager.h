#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

namespace gn
{
  class ShaderManager
  {
  private:
    static map<string, class Shader*>  m_shaders;

  public:
    ShaderManager() = default;
    ~ShaderManager() = default;

    static const map<string, class Shader*>& get();

    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. 
    // If gShaderFile is not nullptr, it also loads a geometry shader
    void loadShader(
      const string& vShaderFilePath, 
      const string& fShaderFilePath, 
      const string& name);

    // retrieves a stored sader
    class Shader* getShader(const string& name) const;

    // load all shaders
    void init();
    
    // properly de-allocates all loaded resources
    void free();
  };
  
}

#endif