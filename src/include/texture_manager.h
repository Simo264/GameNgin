#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

namespace gn
{
  class TextureManager
  {
  private:
    static std::map<std::string, class Texture*> m_textures;

    class Texture* loadTextureFromFile(const char* file, bool alpha);

  public:
    TextureManager() = default;
    ~TextureManager() = default;

    static const std::map<std::string, class Texture*>& get();

    // loads (and generates) a texture from file
    void loadTexture(const char* filePath, bool alpha, const std::string& name);

    // retrieves a stored texture
    class Texture* getTexture(const std::string& name);

    // properly de-allocates all loaded resources
    void free();
  };
}


#endif
