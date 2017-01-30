#include "Base.h"
#include "OBJLoader.h"
#include "Utility.h"
#include "ShaderManager.h"
#include "Lights.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

Base::~Base(void)
{
}

const bool Base::Initialize()
{
	// Load in config file here
	vector<string> configLines;
	if(!Utility::Instance()->LoadConfigFile("Resources/Config/Config.txt", configLines))
		return false;

	map<string, string> config;
	if(!Utility::Instance()->ReturnConfigField(config, "Base", configLines))
		return false;

	OBJLoader obj;
	vector<Utility::Vertex> faces;

	if(!obj.LoadFaces(config["OBJFile"].c_str(), faces))
		return false;

	_vbo.CreateVBO(faces);

	Vector3f pos, scale, rotation;

	Utility::Instance()->StringToVector(config["Position"], pos);
	Utility::Instance()->StringToVector(config["Scale"], scale);
	Utility::Instance()->StringToVector(config["Rotation"], rotation);

	Pos(pos);
	Size(scale);
	Rotation(rotation);

	Vector4f amb, dif, spec;
	float shine;

	Utility::Instance()->StringToVector(config["Ambience"], amb);
	Utility::Instance()->StringToVector(config["Diffuse"], dif);
	Utility::Instance()->StringToVector(config["Specular"], spec);
	shine = (float)atof(config["Shine"].c_str());

	InitializeTexture(config["TextureFile"].c_str());
	
	ShaderManager::Instance()->AddNewShader("Base", 
		"Resources/Shaders/Base.vert",
		"Resources/Shaders/Base.frag");
	ShaderManager::Instance()->UseProgram("Base");
	ShaderManager::Instance()->AddAttribTo("Base", "aTexCoord", 2, 12);
	ShaderManager::Instance()->AddAttribTo("Base", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("Base", "aNormal", 3, 20);
	ShaderManager::Instance()->AddUniformTo("Base", "texSampler");
	ShaderManager::Instance()->AddUniformTo("Base", "uShine");
	ShaderManager::Instance()->AddUniformTo("Base", "uDif");
	ShaderManager::Instance()->AddUniformTo("Base", "uSpec");
	ShaderManager::Instance()->AddUniformTo("Base", "uAmb");
	ShaderManager::Instance()->AddUniformTo("Base", "uLightDir");
	ShaderManager::Instance()->UseUniform1i("Base", "texSampler", 0);
	ShaderManager::Instance()->UseUniform4fv("Base", "uAmb", amb);
	ShaderManager::Instance()->UseUniform4fv("Base", "uDif", dif);
	ShaderManager::Instance()->UseUniform4fv("Base", "uSpec", spec);
	ShaderManager::Instance()->UseUniform1f("Base", "uShine", shine);
	ShaderManager::Instance()->UnuseProgram("Base");

	return true;
}

const void Base::Render( const bool sun )
{
	if(sun)
	{
		glPushMatrix();
		glTranslatef(Pos()[0], Pos()[1], Pos()[2]);
		_vbo.BindBuffer();
		BindTexture();
		ShaderManager::Instance()->UseProgram("Base");
		ShaderManager::Instance()->UseUniform3fv("Base", "uLightDir", Lights::Instance()->GetSunDirection());
		_vbo.Render(GL_TRIANGLES);
		ShaderManager::Instance()->UnuseProgram("Base");
		UnbindTexture();
		_vbo.UnbindBuffer();
		glPopMatrix();
	}
	else
	{

	}
}
