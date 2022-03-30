#pragma once
#include <string>
#include "Glew/include/glew.h"
#include "transform.h"
#include "Camera.h"
#include <iostream>
#include <fstream>

enum class ShaderType
{
	SH_Vertex,
	SH_Frag,
	SH_Geometry,
	SH_Max
};

class Shader
{
public:
	Shader();

	void Bind(); //Set gpu to use our shaders
	void Update(const Transform& transform, const Camera& camera);
	void init(const std::string&);

	int GetTypeMacro(ShaderType type);
	GLuint Compile(const char* fileBuffer, ShaderType type, const GLint size);

	std::string Shader::LoadShader(const std::string& fileName);
	void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint Shader::CreateShader(const std::string& text, unsigned int type);

    ~Shader();

	// ------------------------------------------------------------------------
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), (int)value);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderID, name.c_str()), value);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(shaderID, name.c_str()), value);

		//if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		//{
		//	std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
		//	__debugbreak();
		//}
	}
	// ------------------------------------------------------------------------
	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec2(const std::string& name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(shaderID, name.c_str()), x, y);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec3(const std::string& name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(shaderID, name.c_str()), x, y, z);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(shaderID, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void setVec4(const std::string& name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(shaderID, name.c_str()), x, y, z, w);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat2(const std::string& name, const glm::mat2& mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat3(const std::string& name, const glm::mat3& mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void setMat4(const std::string& name, const glm::mat4& mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(shaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(shaderID, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}


protected:
private:

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint shaderID; // Track the shader program
	GLuint shaders[static_cast<int>(ShaderType::SH_Max)]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
