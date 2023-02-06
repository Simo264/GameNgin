#ifndef SHADER_H
#define SHADER_H

// Shader class
// -----------------------------------------------------------
namespace gn
{
  class Shader
  {
  private:
    uint32_t m_shaderOBJ;

    // checks if compilation or linking failed and if so, print the error logs
    bool checkCompileErrors(uint32_t object, const std::string& type); 

  public:
    // constructors
    Shader() = default;
    
    // destructor
    ~Shader() { glDeleteProgram(m_shaderOBJ); }

    // compiles the shader from given source code
    bool compile(const char* vertexSource, const char* fragmentSource);
    
    // sets the current shader as active
    void use();

    // utility functions
    void setFloat    (const char* name, float value);
    void setInteger  (const char* name, int value);
    void setVector2f (const char* name, const vec2& value);
    void setVector3f (const char* name, const vec3& value);
    void setVector4f (const char* name, const vec4& value);
    void setMatrix4  (const char* name, const mat4& matrix);
  };
  // -----------------------------------------------------------

}




#endif