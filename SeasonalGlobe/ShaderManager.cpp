#include "ShaderManager.h"

ShaderManager* ShaderManager::_instance = NULL;

ShaderManager::ShaderManager(void)
{
}

ShaderManager::~ShaderManager(void)
{
}

const void ShaderManager::AddNewShader( const char* name, const char* vert, const char* frag)
{
	_listOfShaders[name] = new ShaderProgram();
	_listOfShaders[name]->LoadShaders(vert,frag);
	_listOfShaders[name]->Link();
}

const void ShaderManager::AddAttribTo( const char* shaderName, const char* attribName, const int size, const int offset )
{
	_listOfShaders[shaderName]->AddAttribute(attribName, size, offset);
}

const void ShaderManager::AddUniformTo( const char* shaderName, const char* uniName )
{
	_listOfShaders[shaderName]->AddUniform(uniName);
}

const GLint ShaderManager::GetUniformLoc( const char* shaderName, const char* uniLoc )
{
	return _listOfShaders[shaderName]->GetUniformLocation(uniLoc);
}

const void ShaderManager::UseProgram( const char* name )
{
	_listOfShaders[name]->Use();
}

const void ShaderManager::UnuseProgram(const char* name)
{
	_listOfShaders[name]->Unuse();
}
