#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "engine/core/design_pattern/singleton.h"

namespace gn
{
  // TextureManager class
  // -------------------------------
  class TextureManager : public Singleton<TextureManager>
  {
  private:
    map<string, class Texture*> m_textures;
    
    class Texture* loadTextureFromFile(const string& file, bool alpha);

  public:
    const map<string, class Texture*>& getTextures() const { return m_textures; }

    // loads (and generates) a texture from file
    void loadTexture(const string& filePath, bool alpha, const string& name);

    // retrieves a stored texture
    class Texture* getTextureByName(const string& name);

    // load all textures
    void init();
    
    // properly de-allocates all loaded resources
    void free();
  };
}


#endif
