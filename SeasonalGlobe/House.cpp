#include "House.h"
#include "OBJLoader.h"
#include "Utility.h"
#include "ShaderManager.h"
#include "Lights.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

House::~House(void)
{
}

const bool House::Initialize()
{
	// Load in config file here
	vector<string> configLines;
	if(!Utility::Instance()->LoadConfigFile("Resources/Config/Config.txt", configLines))
		return false;

	map<string, string> config;
	if(!Utility::Instance()->ReturnConfigField(config, "House", configLines))
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
	
	ShaderManager::Instance()->AddNewShader("House", 
		"Resources/Shaders/House.vert",
		"Resources/Shaders/House.frag");
	ShaderManager::Instance()->UseProgram("House");
	ShaderManager::Instance()->AddAttribTo("House", "aTexCoord", 2, 12);
	ShaderManager::Instance()->AddAttribTo("House", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("House", "aNormal", 3, 20);
	ShaderManager::Instance()->AddUniformTo("House", "texSampler");
	ShaderManager::Instance()->AddUniformTo("House", "uShine");
	ShaderManager::Instance()->AddUniformTo("House", "uDif");
	ShaderManager::Instance()->AddUniformTo("House", "uSpec");
	ShaderManager::Instance()->AddUniformTo("House", "uAmb");
	ShaderManager::Instance()->AddUniformTo("House", "uLightDir");
	ShaderManager::Instance()->AddUniformTo("House", "percThroughSeason");
	ShaderManager::Instance()->UseUniform1i("House", "texSampler", 0);
	ShaderManager::Instance()->UseUniform4fv("House", "uAmb", amb);
	ShaderManager::Instance()->UseUniform4fv("House", "uDif", dif);
	ShaderManager::Instance()->UseUniform4fv("House", "uSpec", spec);
	ShaderManager::Instance()->UseUniform1f("House", "uShine", shine);
	ShaderManager::Instance()->UnuseProgram("House");

	return true;
}

const void House::Render( const bool sun )
{
	if(sun)
	{
		glPushMatrix();
		glTranslatef(Pos()[0], Pos()[1], Pos()[2]);
		_vbo.BindBuffer();
		BindTexture();
		ShaderManager::Instance()->UseProgram("House");
		ShaderManager::Instance()->UseUniform3fv("House", "uLightDir", Lights::Instance()->GetSunDirection());
		ShaderManager::Instance()->UseUniform1f("House", "percThroughSeason", _percThroughSeason);
		_vbo.Render(GL_TRIANGLES);
		ShaderManager::Instance()->UnuseProgram("House");
		UnbindTexture();
		_vbo.UnbindBuffer();
		glPopMatrix();
	}
	else
	{

	}
}
