#include "Globe.h"
#include "OBJLoader.h"
#include "Utility.h"
#include "ShaderManager.h"
#include "Lights.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

Globe::~Globe(void)
{
}

const bool Globe::Initialize()
{
	vector<string> configLines;
	if(!Utility::Instance()->LoadConfigFile("Resources/Config/Config.txt", configLines))
		return false;

	map<string, string> config;
	if(!Utility::Instance()->ReturnConfigField(config, "Globe", configLines))
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

	ShaderManager::Instance()->AddNewShader("Globe", 
		"Resources/Shaders/Globe.vert",
		"Resources/Shaders/Globe.frag");

	ShaderManager::Instance()->UseProgram("Globe");
	ShaderManager::Instance()->AddAttribTo("Globe", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("Globe", "aNormal", 3, 20);
	ShaderManager::Instance()->AddUniformTo("Globe", "uShine");
	ShaderManager::Instance()->AddUniformTo("Globe", "uDif");
	ShaderManager::Instance()->AddUniformTo("Globe", "uSpec");
	ShaderManager::Instance()->AddUniformTo("Globe", "uAmb");
	ShaderManager::Instance()->AddUniformTo("Globe", "uLightDir");

	ShaderManager::Instance()->UseUniform4fv("Globe", "uAmb", amb);
	ShaderManager::Instance()->UseUniform4fv("Globe", "uDif",dif);
	ShaderManager::Instance()->UseUniform4fv("Globe", "uSpec",spec);
	ShaderManager::Instance()->UseUniform1f("Globe", "uShine", shine);

	ShaderManager::Instance()->UnuseProgram("Globe");

	return true;
}

const void Globe::Render( const bool sun )
{
	if (sun)
	{
		glPushMatrix();
		glTranslatef(Pos()[0], Pos()[1], Pos()[2]);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		_vbo.BindBuffer();
		ShaderManager::Instance()->UseProgram("Globe");
		ShaderManager::Instance()->UseUniform3fv("Globe", "uLightDir", Lights::Instance()->GetSunDirection());
		_vbo.Render(GL_TRIANGLES);
		ShaderManager::Instance()->UnuseProgram("Globe");
		_vbo.UnbindBuffer();
		glDisable(GL_BLEND);
		glPopMatrix();
	}
	else
	{

	}
}
