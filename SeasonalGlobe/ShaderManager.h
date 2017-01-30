//////////////////////////////////////////////
// ShaderManager
//--------------------------------------------
// Created By: Devon Hansen
//--------------------------------------------
// Parasoft warnings:
//--------------------------------------------
// Description: Holds all the shaders the user defines as needed. 
// Lets the user start the program wanted, 
// add attributes and uniforms, then stop afterwards
#pragma once
#include <map>
#include <string>
#include "ShaderProgram.h"
#include "Utility.h"
#include "GXBase/include/GXBase.h"

class ShaderManager
{
private:
	ShaderManager(const ShaderManager&);
	ShaderManager& operator=(const ShaderManager&);

	map<std::string, ShaderProgram*> _listOfShaders;

	static ShaderManager* _instance;

protected:
	ShaderManager(void);

public:
	~ShaderManager(void);

	static ShaderManager* Instance()
	{
		if (_instance == 0)
		{
			_instance = new ShaderManager();
		}

		return _instance;
	}

	const void AddNewShader(const char* name, const char* vert, const char* frag);
	const void AddAttribTo(const char* shaderName, const char* attribName, const int size, const int offset);
	const void AddUniformTo(const char* shaderName, const char* uniName);

	const GLint GetUniformLoc(const char* shaderName, const char* uniLoc);

	const void UseProgram(const char* name);
	const void UnuseProgram(const char* name);

	const void UseUniform1i(const char* shaderName, const char* uniName, const int i)
	{
		_listOfShaders[shaderName]->UseUniform1i(uniName, i);
	}

	const void UseUniform1f(const char* shaderName, const char* uniName, const float f)
	{
		_listOfShaders[shaderName]->UseUniform1f(uniName, f);
	}

	const void UseUniform2f(const char* shaderName, const char* uniName, const float f1, const float f2)
	{
		_listOfShaders[shaderName]->UseUniform2f(uniName, f1, f2);
	}

	const void UseUniform3f(const char* shaderName, const char* uniName, const float f1, const float f2, const float f3)
	{
		_listOfShaders[shaderName]->UseUniform3f(uniName, f1, f2, f3);
	}

	const void UseUniform4f(const char* shaderName, const char* uniName, const float f1, const float f2, const float f3, const float f4)
	{
		_listOfShaders[shaderName]->UseUniform4f(uniName, f1, f2, f3, f4);
	}

	const void UseUniform2fv(const char* shaderName, const char* uniName, const Vector2f& v)
	{
		_listOfShaders[shaderName]->UseUniform2fv(uniName, v);
	}

	const void UseUniform3fv(const char* shaderName, const char* uniName, const Vector3f& v)
	{
		_listOfShaders[shaderName]->UseUniform3fv(uniName, v);
	}

	const void UseUniform4fv(const char* shaderName, const char* uniName, const Vector4f& v)
	{
		_listOfShaders[shaderName]->UseUniform4fv(uniName, v);
	}
};

