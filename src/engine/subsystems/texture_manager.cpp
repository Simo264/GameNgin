#include "engine/core/core.h"

#include "texture_manager.h"
#include "file_manager.h"

#include "engine/texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace gn
{
  map<string, Texture*> TextureManager::m_textures = map<string, Texture*>();

  const map<string, class Texture*>& TextureManager::get()
  {
    return m_textures;
  }

  Texture* TextureManager::getTexture(const string& name)
  {
    return m_textures.at(name);
  }

  void TextureManager::loadTexture(const string& file, bool alpha, const string& name)
  {
    Texture* texture = loadTextureFromFile(file, alpha);
    m_textures.insert({name , texture}); 
  }
  
  Texture* TextureManager::loadTextureFromFile(const string& filePath, bool alpha)
  {
    // create texture object
    Texture* texture = new Texture;
    if (alpha)
    {
      texture->internalFormat = GL_RGBA;
      texture->imageFormat    = GL_RGBA;
    }

    stbi_set_flip_vertically_on_load(1);

    // load image
    int width, height, nrChannels;
    u_char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    // now generate texture
    texture->generate(vec2ui(width, height), data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
  }

  void TextureManager::init()
  {
    vector<string> buffer;
    FileManager::read(TEXTURES_INI_FILE, buffer);

    array<char, 50>  texturename;
    array<char, 100> texturepath;
    array<char, 5>   fileextension;

    array<char, 20> key;
    array<char, 50> value;

    for(auto it = buffer.begin(); it != buffer.end(); ++it)
    {
      if(it->empty()) continue;

      texturename.fill(0);
      texturepath.fill(0);
      fileextension.fill(0);
      key.fill(0);
      value.fill(0);

      copy_n(it->begin() + 1, it->size() - 2, texturename.begin());

      ++it;
      
      int delimiter = it->find("=");
      
      copy_n(it->begin(), delimiter, key.begin());
      copy(it->begin() + delimiter + 1, it->end(), value.begin()); 
      copy(value.begin(), value.end(), texturepath.begin());

      delimiter = it->find_last_of(".");

      copy(it->begin() + delimiter, it->end(), fileextension.begin());
      
      bool alpha = false;
      if(strcmp(fileextension.data(), ".png") == 0) 
        alpha = true;

      loadTexture(texturepath.data(), alpha, texturename.data());
    }
  }

  void TextureManager::free()
  {
    for(auto it = m_textures.begin(); it != m_textures.end(); ++it)
      delete it->second;
    m_textures.clear();
  }

}
