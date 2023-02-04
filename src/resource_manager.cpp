#include "include/core_minimal.h"
#include "include/resource_manager.h"
#include "include/logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

namespace gn
{

  // Instantiate static variables
  std::map<std::string, Shader*>  ResourceManager::shaders;
  std::map<std::string, Texture*> ResourceManager::textures;


  Shader* ResourceManager::loadShader(
    const char* vShaderFile, 
    const char* fShaderFile, 
    const char* gShaderFile, 
    const std::string& name)
  {
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
    return shaders[name];
  }

  Shader* ResourceManager::getShader(const std::string& name)
  {
    return shaders[name];
  }

  Texture* ResourceManager::loadTexture(const char* file, bool alpha, const std::string& name)
  {
    textures[name] = loadTextureFromFile(file, alpha);
    return textures[name];
  }

  Texture* ResourceManager::getTexture(const std::string& name)
  {
    return textures[name];
  }

  void ResourceManager::free()
  {
    // (properly) delete all shaders	
    for (auto iter : shaders)
      delete iter.second;
    // (properly) delete all textures
    for (auto iter : textures)
      delete iter.second;
  }

  Shader* ResourceManager::loadShaderFromFile(
    const char* vShaderFile, 
    const char* fShaderFile, 
    const char* gShaderFile)
  {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try
    {
      // open files
      std::ifstream vertexShaderFile(vShaderFile);
      std::ifstream fragmentShaderFile(fShaderFile);
      std::stringstream vShaderStream, fShaderStream;
      // read file's buffer contents into streams
      vShaderStream << vertexShaderFile.rdbuf();
      fShaderStream << fragmentShaderFile.rdbuf();
      // close file handlers
      vertexShaderFile.close();
      fragmentShaderFile.close();
      // convert stream into string
      vertexCode = vShaderStream.str();
      fragmentCode = fShaderStream.str();
      // if geometry shader path is present, also load a geometry shader
      if (gShaderFile != nullptr)
      {
        std::ifstream geometryShaderFile(gShaderFile);
        std::stringstream gShaderStream;
        gShaderStream << geometryShaderFile.rdbuf();
        geometryShaderFile.close();
        geometryCode = gShaderStream.str();
      }
    }
    catch (std::exception e)
    {
      LOG_ERROR("ERROR::SHADER: Failed to read shader files");
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    // 2. now create shader object from source code
    Shader* shader = new Shader;
    shader->compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
    return shader;
  }

  Texture* ResourceManager::loadTextureFromFile(const char* file, bool alpha)
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
    u_char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    texture->generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
  }

}
