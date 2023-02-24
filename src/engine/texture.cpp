#include "engine/core/core.h"
#include "engine/texture.h"

namespace gn
{
  void Texture::generate(const vec2ui& size, u_char* data)
  {
    m_size = size;

    // create Texture
    glBindTexture(GL_TEXTURE_2D, m_textureOBJ);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, size.x, size.y, 0, imageFormat, GL_UNSIGNED_BYTE, data);
    
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);
  }
}