#include "Lake.h"
#include "OBJLoader.h"
#include "Utility.h"
#include "ShaderManager.h"
#include "Lights.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

Lake::~Lake(void)
{
}

const bool Lake::Initialize()
{
	vector<string> configLines;
	if(!Utility::Instance()->LoadConfigFile("Resources/Config/Config.txt", configLines))
		return false;

	map<string, string> config;
	if(!Utility::Instance()->ReturnConfigField(config, "Lake", configLines))
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

	ShaderManager::Instance()->AddNewShader("Lake", 
		"Resources/Shaders/Lake.vert",
		"Resources/Shaders/Lake.frag");

	ShaderManager::Instance()->UseProgram("Lake");
	ShaderManager::Instance()->AddAttribTo("Lake", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("Lake", "aNormal", 3, 20);
	ShaderManager::Instance()->AddAttribTo("Lake", "aTexture", 2, 12);
	ShaderManager::Instance()->AddUniformTo("Lake", "uShine");
	ShaderManager::Instance()->AddUniformTo("Lake", "uDif");
	ShaderManager::Instance()->AddUniformTo("Lake", "uSpec");
	ShaderManager::Instance()->AddUniformTo("Lake", "uAmb");
	ShaderManager::Instance()->AddUniformTo("Lake", "uLightDir");
	ShaderManager::Instance()->AddUniformTo("Lake", "uTexture");
	ShaderManager::Instance()->UseUniform1i("Lake", "uTexture", 0);
	ShaderManager::Instance()->UseUniform4fv("Lake", "uAmb", amb);
	ShaderManager::Instance()->UseUniform4fv("Lake", "uDif",dif);
	ShaderManager::Instance()->UseUniform4fv("Lake", "uSpec",spec);
	ShaderManager::Instance()->UseUniform1f("Lake", "uShine", shine);

	ShaderManager::Instance()->UnuseProgram("Lake");

	if(!Utility::Instance()->ReturnConfigField(config, "Terrain", configLines))
		return false;

	InitializeTexture(config["TextureFile"].c_str());

	return true;
}

const void Lake::Render( const bool sun )
{
	if(sun)
	{
		glPushMatrix();
		glTranslatef(Pos()[0], Pos()[1], Pos()[2]);
		glEnable(GL_BLEND);
 		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		BindTexture();
		_vbo.BindBuffer();
		ShaderManager::Instance()->UseProgram("Lake");
		ShaderManager::Instance()->UseUniform3fv("Lake", "uLightDir", Lights::Instance()->GetSunDirection());
		_vbo.Render(GL_TRIANGLES);
		ShaderManager::Instance()->UnuseProgram("Lake");
		_vbo.UnbindBuffer();
		UnbindTexture();
		glDisable(GL_BLEND);
		glPopMatrix();
	}
	else
	{
	}
}
