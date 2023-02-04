#include "include/core_minimal.h"
#include "include/shader.h"

Shader::Shader(const char* vsFilename, const char* fsFilename, const char* gsFilename)
{
	std::string vsSource, fsSource, gsSource;

	std::ifstream vShaderFile, fShaderFile, gShaderFile;
	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		std::stringstream vShaderStream, fShaderStream, gShaderStream;

		vShaderFile.open(vsFilename);
		vShaderStream << vShaderFile.rdbuf();	// read file's buffer contents into streams
		vShaderFile.close();
		vsSource = vShaderStream.str();	// convert stream into string 

		fShaderFile.open(fsFilename);
		fShaderStream << fShaderFile.rdbuf(); // read file's buffer contents into streams
		fShaderFile.close();
		fsSource = fShaderStream.str();	// convert stream into string 
		
		if(gsFilename)
		{
			gShaderFile.open(gsFilename);
			gShaderStream << gShaderFile.rdbuf();
			gShaderFile.close();
			gsSource = gShaderStream.str();
		}
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
	}

	// 2. compile shaders
	compile(
		vsSource.c_str(), 
		fsSource.c_str(), 
		(gsSource.size() == 0 ? nullptr : gsSource.c_str())
	);	
}

void Shader::use()
{
	glUseProgram(m_shaderOBJ);
}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource)
{
	uint32_t sVertex, sFragment, gShader;
	// vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");
	// fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");
	// if geometry shader source code is given, also compile geometry shader
	if (geometrySource != nullptr)
	{
		gShader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(gShader, 1, &geometrySource, NULL);
		glCompileShader(gShader);
		checkCompileErrors(gShader, "GEOMETRY");
	}
	// shader program
	m_shaderOBJ = glCreateProgram();
	glAttachShader(m_shaderOBJ, sVertex);
	glAttachShader(m_shaderOBJ, sFragment);
	if (geometrySource != nullptr)
		glAttachShader(m_shaderOBJ, gShader);
	glLinkProgram(m_shaderOBJ);
	checkCompileErrors(m_shaderOBJ, "PROGRAM");
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometrySource != nullptr)
		glDeleteShader(gShader);
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

void Shader::checkCompileErrors(uint32_t object, const std::string& type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
	}
}
