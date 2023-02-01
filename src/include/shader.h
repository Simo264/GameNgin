#ifndef SHADER_H
#define SHADER_H

// Shader class
// -----------------------------------------------------------
class Shader
{
private:
  uint32_t m_shaderOBJ;

  // checks if compilation or linking failed and if so, print the error logs
  void checkCompileErrors(uint32_t object, const std::string& type); 

public:

  // constructors
  Shader(
    const char* vsFilename, 
    const char* fsFilename, 
    const char* gsFilename = nullptr);
  Shader() { }

  ~Shader() { glDeleteProgram(m_shaderOBJ); }
  
  // sets the current shader as active
  void use();

  // compiles the shader from given source code
  void compile(
    const char* vertexSource, 
    const char* fragmentSource, 
    const char* geometrySource = nullptr);
  
  // utility functions
  void setFloat    (const char*name, float value);
  void setInteger  (const char*name, int value);
  void setVector2f (const char*name, const vec2& value);
  void setVector3f (const char*name, const vec3& value);
  void setVector4f (const char*name, const vec4& value);
  void setMatrix4  (const char*name, const mat4& matrix);
};
// -----------------------------------------------------------
#endif