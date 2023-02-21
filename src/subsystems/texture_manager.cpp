#include "../core_minimal.h"

#include "texture_manager.h"
#include "file_manager.h"

#include "../texture.h"

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

  void TextureManager::loadTexture(const std::string& file, bool alpha, const std::string& name)
  {
    Texture* texture = loadTextureFromFile(file, alpha);
    m_textures.insert({name , texture}); 
  }
  
  Texture* TextureManager::loadTextureFromFile(const std::string& filePath, bool alpha)
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
    std::string buffer;
    FileManager::read(TEXTURES_INI_FILE, buffer);
    
    std::vector<std::string> bufferlines;
    bufferlines.reserve(std::count(buffer.begin(), buffer.end(), '\n'));

    std::array<char, 100> bufferline;
    bufferline.fill(0);

    int indexbl = 0;
    for(char& c : buffer)
    {
      if(c == '\n')
      {
        if(strlen(bufferline.data()) != 0)
          bufferlines.push_back(bufferline.data());
        
        bufferline.fill(0);
        indexbl = 0;
      }
      else
        bufferline[indexbl++] = c;
    }


    std::array<char, 50> texturename;
    std::array<char, 100> texturepath;
    std::array<char, 5> fileextension;

    std::array<char, 20> key;
    std::array<char, 50> value;

    for(auto it = bufferlines.begin(); it != bufferlines.end(); ++it)
    {
      texturename.fill(0);
      texturepath.fill(0);
      fileextension.fill(0);
      key.fill(0);
      value.fill(0);

      std::copy_n(it->begin() + 1, it->size() - 2, texturename.begin());

      ++it;
      
      int delimiter = it->find("=");
      
      std::copy_n(it->begin(), delimiter, key.begin());
      std::copy(it->begin() + delimiter + 1, it->end(), value.begin()); 
      std::copy(value.begin(), value.end(), texturepath.begin());

      delimiter = it->find_last_of(".");

      std::copy(it->begin() + delimiter, it->end(), fileextension.begin());
      
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
