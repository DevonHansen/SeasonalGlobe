#include "Shader.h"
using namespace std;

Shader::Shader(SHADER_TYPE type)
	:_type(type)
{
	glex::Load();
	if (_type == VERTEX) { _handle = glCreateShader(GL_VERTEX_SHADER); }
	else { _handle = glCreateShader(GL_FRAGMENT_SHADER); }
	_source = 0;
}

Shader::~Shader(void)
{
	delete _source;
}

const void Shader::LoadFromFile( const char* filepath )
{
	if(_source != 0)
		delete _source;

	ifstream in(filepath);

	if (!in)
	{
#ifdef _DEBUG
		cout << "Error loading from file " << filepath << endl;
#endif // _DEBUG
		return;
	}

#ifdef _DEBUG
	cout << "Loading Shader source file successful " << filepath << endl;
#endif // _DEBUG
	_source = new string((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
	in.close();

	*_source += "\0";		// Need terminating character

	const char* data = _source->c_str();

	glShaderSource(_handle, 1, &data, NULL);
}

const void Shader::Compile()
{
#ifdef _DEBUG
	if (_source == 0)
	{
		cout << "No shader source loaded" << endl;
		return;
	}
#endif // _DEBUG

	glCompileShader(_handle);

#ifdef _DEBUG
	GLint infologLength = 0;
	GLint charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(_handle, GL_INFO_LOG_LENGTH,&infologLength);
	cout<<"info log length "<<infologLength<<"\n";
	if(infologLength > 0)
	{
		infoLog = new char[infologLength];
		glGetShaderInfoLog(_handle, infologLength, &charsWritten, infoLog);

		cout<<infoLog<<endl;
		delete [] infoLog;
		glGetShaderiv(_handle, GL_COMPILE_STATUS,&infologLength);
		if( infologLength == GL_FALSE)
		{
			cout << "Shader compile failed or had warnings " << _source->c_str() << endl;
		}
	}
#endif // _DEBUG
}
