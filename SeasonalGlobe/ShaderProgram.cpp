#include "ShaderProgram.h"
#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG
using namespace std;

ShaderProgram::ShaderProgram(void)
	: _vertShader(NULL), _fragShader(NULL)
{
	glex::Load();
	_ID = glCreateProgram();
}


ShaderProgram::~ShaderProgram(void)
{
	delete _vertShader;
	delete _fragShader;
}

const void ShaderProgram::UseAttribute( const char* name )
{
	glVertexAttribPointer(_attributes[name]._location, _attributes[name]._size,
		GL_FLOAT, false, sizeof(Utility::Vertex), Utility::Instance()->BufferOffset(_attributes[name]._offset));
}

const void ShaderProgram::Use()
{
	glUseProgram(_ID);

	map<string, Attributes>::const_iterator i;

	for (i = _attributes.begin(); i != _attributes.end(); ++i)
	{
		glEnableVertexAttribArray(i->second._location);
		UseAttribute(i->first.c_str());
	}
}

const void ShaderProgram::Unuse()
{
	map<string, Attributes>::const_iterator i;

	for (i = _attributes.begin(); i != _attributes.end(); ++i)
	{
		glDisableVertexAttribArray(i->second._location);
	}

	glUseProgram(0);
}

const void ShaderProgram::AddAttribute( const char* name, const int size, const int offset )
{
	_attributes[name]._location = glGetAttribLocation(_ID, name);
	_attributes[name]._size = size;
	_attributes[name]._offset = offset;
}

const void ShaderProgram::AddUniform( const char* name )
{
	_uniforms[name] = glGetUniformLocation(_ID, name);
}

const GLint ShaderProgram::GetUniformLocation(const char* name) 
{
	return _uniforms[name];
}

const void ShaderProgram::LoadShaders( const char* vertFile, const char* fragFile )
{
	_vertShader = new Shader(Shader::VERTEX);
	_vertShader->LoadFromFile(vertFile);
	_vertShader->Compile();

	glAttachShader(_ID, _vertShader->ShaderHandle());

	_fragShader = new Shader(Shader::FRAGMENT);
	_fragShader->LoadFromFile(fragFile);
	_fragShader->Compile();

	glAttachShader(_ID, _fragShader->ShaderHandle());
}

const void ShaderProgram::Link()
{
	glLinkProgram(_ID);

	GLint infologLength = 0;

	glGetProgramiv(_ID,GL_INFO_LOG_LENGTH,&infologLength);
#ifdef _DEBUG
	cout<<"Link Log Length "<<infologLength<<endl;
#endif
	if(infologLength > 0)
	{
		char *infoLog = new char[infologLength];
		GLint charsWritten  = 0;

		glGetProgramInfoLog(_ID, infologLength, &charsWritten, infoLog);

#ifdef _DEBUG
		cout<<infoLog<<endl;
#endif // _DEBUG
		delete [] infoLog;
		glGetProgramiv(_ID, GL_LINK_STATUS,&infologLength);
		if( infologLength == GL_FALSE)
		{
#ifdef _DEBUG
			cout<<"Program link failed exiting" << endl;
#endif
		}
	}
}
