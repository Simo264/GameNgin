/*******************************************************************
** This code is part of Breakout.
**
** Breakout is free software: you can redistribute it and/or modify
** it under the terms of the CC BY 4.0 license as published by
** Creative Commons, either version 4 of the License, or (at your
** option) any later version.
******************************************************************/
#ifndef SHADER_H
#define SHADER_H

// General purpose shader object. Compiles from file, generates
// compile/link-time error messages and hosts several utility 
// functions for easy management.
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
  void setVector2f (const char*name, const glm::vec2& value);
  void setVector3f (const char*name, const glm::vec3& value);
  void setVector4f (const char*name, const glm::vec4& value);
  void setMatrix4  (const char*name, const glm::mat4& matrix);
};

#endif