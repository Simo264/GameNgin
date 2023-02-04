#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "shader.h"
#include "texture.h"

// ResourceManager class
// -----------------------------------------------------------

namespace gn
{
  class ResourceManager
  {
  public:
    // resource storage
    static std::map<std::string, Shader*>  shaders;
    static std::map<std::string, Texture*> textures;

    // loads (and generates) a shader program from file loading vertex, fragment (and geometry) shader's source code. 
    // If gShaderFile is not nullptr, it also loads a geometry shader
    static Shader* loadShader(
      const char* vShaderFile, 
      const char* fShaderFile, 
      const char* gShaderFile, 
      const std::string& name);

    // retrieves a stored sader
    static Shader* getShader(const std::string& name);

    // loads (and generates) a texture from file
    static Texture* loadTexture(const char* file, bool alpha, const std::string& name);

    // retrieves a stored texture
    static Texture* getTexture(const std::string& name);

    // properly de-allocates all loaded resources
    static void free();

  private:
    // private constructor, that is we do not want any actual resource manager objects. 
    // Its members and functions should be publicly available (static).
    ResourceManager() = default;
    ~ResourceManager() = default;
    
    // loads and generates a shader from file
    static Shader* loadShaderFromFile(
      const char* vShaderFile, 
      const char* fShaderFile, 
      const char* gShaderFile = nullptr);
    
    // loads a single texture from file
    static Texture* loadTextureFromFile(const char* file, bool alpha);
  };
}
// -----------------------------------------------------------
#endif