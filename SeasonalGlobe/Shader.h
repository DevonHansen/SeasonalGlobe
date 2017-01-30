//////////////////////////////////////////////
// Shader
//--------------------------------------------
// Created By: Devon Hansen
//--------------------------------------------
// Parasoft warnings:
//--------------------------------------------
// Description: Holds data about a shader (either vertex or fragment)
#pragma once
#include <fstream>
#include <string>
#include "GXBase/include/GXBase.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

class Shader : public glex
{
public:
	enum SHADER_TYPE
	{
		VERTEX = 0,
		FRAGMENT
	};

private:
	std::string* _source;
	SHADER_TYPE _type;
	GLuint _handle;

	Shader(const Shader& s);
	Shader& operator=(const Shader& s);

public:
	explicit Shader(SHADER_TYPE type);
	~Shader(void);

	const void LoadFromFile(const char* filepath);

	const void Compile();

	const GLuint ShaderHandle() const { return _handle; }
};