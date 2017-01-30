//////////////////////////////////////////////
// ShaderProgram
//--------------------------------------------
// Created By: Devon Hansen
//--------------------------------------------
// Parasoft warnings:
//--------------------------------------------
// Description: Holds a single shader program.
// Allows user to add attributes, uniforms and run the shader
#pragma once
#include <string>
#include <map>
#include "Shader.h"
#include "Utility.h"
#include "Maths/Vector2f.h"
#include "Maths/Vector3f.h"
#include "Maths/Vector4f.h"
#include "GXBase/include/GXBase.h"
class ShaderProgram : public glex
{
private:
	struct Attributes
	{
		GLint _location;
		int _size;
		int _offset;
	};

	std::map<std::string, GLint> _uniforms;
	std::map<std::string, Attributes> _attributes;

	Shader* _vertShader;
	Shader* _fragShader;
	GLuint _ID;

	const void UseAttribute(const char* name);
	const void UniformLocation(const char* name);

	ShaderProgram(const ShaderProgram&);
	ShaderProgram& operator=(const ShaderProgram&);

public:
	explicit ShaderProgram(void);
	~ShaderProgram(void);

	const void Use();
	const void Unuse();

	const void AddAttribute(const char* name, const int size, const int offset);
	const void AddUniform(const char* name);
	const GLint GetUniformLocation(const char* name);

	const void UseUniform1i(const char* name, const int i)
	{
		glUniform1i(_uniforms[name], i);
	}

	const void UseUniform1f(const char* name, const float f)
	{
		glUniform1f(_uniforms[name], f);
	}

	const void UseUniform2f(const char* name, const float f1, const float f2)
	{
		glUniform2f(_uniforms[name], f1, f2);
	}

	const void UseUniform3f(const char* name, const float f1, const float f2, const float f3)
	{
		glUniform3f(_uniforms[name], f1, f2, f3);
	}

	const void UseUniform4f(const char* name, const float f1, const float f2, const float f3, const float f4)
	{
		glUniform4f(_uniforms[name], f1, f2, f3, f4);
	}

	const void UseUniform2fv(const char* name, const Vector2f& v)
	{
		float data[] = { v[0], v[1] };
		glUniform2fv(_uniforms[name], 1, data);
	}

	const void UseUniform3fv(const char* name, const Vector3f& v)
	{
		float data[] = { v[0], v[1], v[2] };
		glUniform3fv(_uniforms[name], 1, data);
	}

	const void UseUniform4fv(const char* name, const Vector4f& v)
	{
		float data[] = { v[0], v[1], v[2], v[3] };
		glUniform4fv(_uniforms[name], 1, data);
	}

	const void UseUniformMatrix4fv(const char* name, const float* m)
	{
		glUniformMatrix4fv(_uniforms[name], 1, false, m);
	}

	const void LoadShaders(const char* vertFile, const char* fragFile);
	const void Link();

	GLuint ID() const { return _ID; }

	const void Destroy()
	{
		glDeleteShader(_vertShader->ShaderHandle());
		glDeleteShader(_fragShader->ShaderHandle());
		glDeleteProgram(_ID);
	}
};

