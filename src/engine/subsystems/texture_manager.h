#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

namespace gn
{
  class TextureManager
  {
  private:
    static map<string, class Texture*> m_textures;

    class Texture* loadTextureFromFile(const string& file, bool alpha);

  public:
    TextureManager() = default;
    ~TextureManager() = default;

    static const map<string, class Texture*>& get();

    // loads (and generates) a texture from file
    void loadTexture(const string& filePath, bool alpha, const string& name);

    // retrieves a stored texture
    class Texture* getTexture(const string& name);

    // load all textures
    void init();
    
    // properly de-allocates all loaded resources
    void free();
  };
}


#endif
