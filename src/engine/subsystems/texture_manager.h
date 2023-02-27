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
    // return stored data
    const map<string, class Texture*>& getTextures() const { return m_textures; }

    // retrieves a list of texture names
    void getKeys(vector<string>& outNames);

    // retrieves a list of textures
    void getValues(vector<class Texture*>& outTextures);

    // loads (and generates) a texture from file
    void loadTexture(const string& filePath, bool alpha, const string& name);

    // retrieves a stored texture
    class Texture* getTextureByName(const string& name);

    // retrieves a stored texture name
    void getTextureName(const class Texture*, string& outName);


    // load all textures
    void init();
    
    // properly de-allocates all loaded resources
    void free();
  };
}


#endif
