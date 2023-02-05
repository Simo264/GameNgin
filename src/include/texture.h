#ifndef TEXTURE_H
#define TEXTURE_H

namespace gn
{
  // Texture class
  // -----------------------------------------------------------
  class Texture
  {
  private:
    // holds the ID of the texture object, used for all texture operations to reference to this particular texture
    uint32_t m_textureOBJ;
    // texture image dimensions  in pixels
    vec2ui   m_dimension;

  public:
    // set default texture modes
    uint32_t internalFormat = GL_RGB;  // format of texture object
    uint32_t imageFormat    = GL_RGB;  // format of loaded image
    uint32_t wrapS     = GL_REPEAT; // wrapping mode on S axis
    uint32_t wrapT     = GL_REPEAT; // wrapping mode on T axis
    uint32_t filterMin = GL_LINEAR; // filtering mode if texture pixels < screen pixels
    uint32_t filterMax = GL_LINEAR; // filtering mode if texture pixels > screen pixels
    
    Texture()   { glGenTextures(1, &m_textureOBJ);    }
    ~Texture()  { glDeleteTextures(1, &m_textureOBJ); }

    const vec2ui& getDimension() const { return m_dimension; }

    // generates texture from image data
    void generate(const vec2ui& dimension, unsigned char* data);
    
    void use(uint32_t index = 0)  { glActiveTexture(GL_TEXTURE0 + index); }
    
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void bind()   const { glBindTexture(GL_TEXTURE_2D, m_textureOBJ); }
    void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
  };
  // -----------------------------------------------------------

}
#endif