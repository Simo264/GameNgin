#include "core_minimal.h"
#include "texture_manager.h"
#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gn
{
  std::map<std::string, Texture*> TextureManager::m_textures = std::map<std::string, Texture*>();

  const std::map<std::string, class Texture*>& TextureManager::get()
  {
    return m_textures;
  }

  Texture* TextureManager::getTexture(const std::string& name)
  {
    return m_textures.at(name);
  }

  void TextureManager::loadTexture(const char* file, bool alpha, const std::string& name)
  {
    Texture* texture = loadTextureFromFile(file, alpha);
    m_textures.insert({name , texture}); 
  }
  
  Texture* TextureManager::loadTextureFromFile(const char* filePath, bool alpha)
  {
    // create texture object
    Texture* texture = new Texture;
    if (alpha)
    {
      texture->internalFormat = GL_RGBA;
      texture->imageFormat    = GL_RGBA;
    }

    // load image
    int width, height, nrChannels;
    u_char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
    // now generate texture
    texture->generate(vec2ui(width, height), data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
  }

  // properly de-allocates all loaded resources
  void TextureManager::free()
  {
    for(auto it = m_textures.begin(); it != m_textures.end(); ++it)
      delete it->second;
    m_textures.clear();
  }
}
