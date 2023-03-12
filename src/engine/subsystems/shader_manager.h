#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "engine/core/design_pattern/singleton.h"

namespace gn
{
  // Singleton ShaderManager class
  // -------------------------------------------
  class ShaderManager : public Singleton<ShaderManager>
  {
  private:
    map<string, class Shader*> m_shaders;

  public:
    const map<string, class Shader*>& getShaders() const { return m_shaders; }

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
  // -------------------------------------------
}

#endif