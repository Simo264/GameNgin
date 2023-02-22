#include "core_minimal.h"
#include "shader.h"

namespace gn
{
	bool Shader::compile(const char* vertexSource, const char* fragmentSource)
	{
		uint32_t vertexSh, fragmentSh;
		// vertex Shader
		vertexSh = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexSh, 1, &vertexSource, NULL);
		glCompileShader(vertexSh);
		if(!checkCompileErrors(vertexSh, "VERTEX"))
			return false;

		// fragment Shader
		fragmentSh = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentSh, 1, &fragmentSource, NULL);
		glCompileShader(fragmentSh);
		if(!checkCompileErrors(fragmentSh, "FRAGMENT"))
			return false;

		// shader program
		m_shaderOBJ = glCreateProgram();
		glAttachShader(m_shaderOBJ, vertexSh);
		glAttachShader(m_shaderOBJ, fragmentSh);
		glLinkProgram(m_shaderOBJ);
		if(!checkCompileErrors(m_shaderOBJ, "PROGRAM"))
			return false;

		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertexSh);
		glDeleteShader(fragmentSh);

		return true;
	}

	bool Shader::checkCompileErrors(uint32_t object, const std::string& type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(object, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(object, 1024, NULL, infoLog);
				LOG_ERROR(
					std::string("| ERROR::SHADER: Compile-time error: Type: " + type + "\n") + 
					std::string(infoLog));
				return false;
			}
		}
		else
		{
			glGetProgramiv(object, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(object, 1024, NULL, infoLog);
				LOG_ERROR(
					std::string("| ERROR::SHADER: Link-time error: Type: " + type + "\n") + 
					std::string(infoLog));
				return false;
			}
		}
		return true;
	}

	void Shader::use()
	{
		glUseProgram(m_shaderOBJ);
	}

	void Shader::setFloat(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(m_shaderOBJ, name), value);
	}
	void Shader::setInteger(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(m_shaderOBJ, name), value);
	}
	void Shader::setVector2f(const char* name, const vec2& value)
	{
		glUniform2f(glGetUniformLocation(m_shaderOBJ, name), value.x, value.y);
	}
	void Shader::setVector3f(const char* name, const vec3& value)
	{
		glUniform3f(glGetUniformLocation(m_shaderOBJ, name), value.x, value.y, value.z);
	}
	void Shader::setVector4f(const char* name, const vec4& value)
	{
		glUniform4f(glGetUniformLocation(m_shaderOBJ, name), value.x, value.y, value.z, value.w);
	}
	void Shader::setMatrix4(const char* name, const mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_shaderOBJ, name), 1, false, value_ptr(matrix));
	}

}