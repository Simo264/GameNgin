#include "include/core_minimal.h"
#include "include/texture.h"

namespace GL
{
  Texture::Texture()
  {
    glGenTextures(1, &m_textureOBJ);
  }

  void Texture::generate(uint32_t width, uint32_t height, u_char* data)
  {
    this->width   = width;
    this->height  = height;

    // create Texture
    glBindTexture(GL_TEXTURE_2D, m_textureOBJ);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
    
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
  }
}
