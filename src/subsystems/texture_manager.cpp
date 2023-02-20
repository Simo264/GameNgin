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

    std::vector<std::string> lines;
    lines.reserve(std::count(buffer.begin(), buffer.end(), '\n'));

    std::string linebuffer;
    linebuffer.reserve(100);
    for(char c : buffer)
    {
      if(c == '\n')
      {
        if(!linebuffer.empty())
          lines.push_back(linebuffer);
        linebuffer.erase(0, 100);
      }
      else
        linebuffer.push_back(c);
    }

    std::string texturename;
    std::string texturepath;
    texturename.reserve(50);
    texturepath.reserve(100);

    int nline = 0;
    for(std::string& line : lines)
    {
      const int linesize = line.size();
      if(line.at(0) == '[' && line.at(linesize - 1) == ']')
        nline = 0;

      if(nline == 0)
      {
        texturename = line.substr(1, linesize - 2);
      }
      else if(nline == 1)
      {
        texturepath = line;
        
        bool alpha = false;
        if(line.substr(line.find_last_of(".") + 1) == "png")
          alpha = true;

        loadTexture(texturepath, alpha, texturename);
      }

      nline++;
    }
  }

  void TextureManager::free()
  {
    for(auto it = m_textures.begin(); it != m_textures.end(); ++it)
      delete it->second;
    m_textures.clear();
  }

}
