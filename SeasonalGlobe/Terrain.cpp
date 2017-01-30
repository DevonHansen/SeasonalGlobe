#include "Terrain.h"
#include "OBJLoader.h"
#include "Lights.h"
#include "Utility.h"
#include "ShaderManager.h"
#include "ParticleManager.h"
#include <vector>
#include <map>
#include <string>
using namespace std;

Terrain::~Terrain(void)
{
}

const bool Terrain::Initialize()
{
	vector<string> configLines;
	if(!Utility::Instance()->LoadConfigFile("Resources/Config/Config.txt", configLines))
		return false;

	map<string, string> config;
	if(!Utility::Instance()->ReturnConfigField(config, "Terrain", configLines))
		return false;

	OBJLoader obj;
	vector<Utility::Vertex> faces;
	if(!obj.LoadFaces(config["OBJFile"].c_str(), faces))
		return false;

	// Find out where the particles will land and place these in colour
	// section of the vertex
	ParticleManager::Instance()->GetSnowDrifts(faces);

	// Grass needs to know the position of the lake
	_grass.LakeFaces(faces);

	_grass.Initialize();

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

	ShaderManager::Instance()->AddNewShader("Terrain", 
		"Resources/Shaders/Terrain.vert",
		"Resources/Shaders/Terrain.frag");
	ShaderManager::Instance()->UseProgram("Terrain");
	ShaderManager::Instance()->AddAttribTo("Terrain", "aTexCoord", 2, 12);
	ShaderManager::Instance()->AddAttribTo("Terrain", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("Terrain", "aNormal", 3, 20);
	ShaderManager::Instance()->AddAttribTo("Terrain", "aDisScale", 1, 32);
	ShaderManager::Instance()->AddUniformTo("Terrain", "texSampler");
	ShaderManager::Instance()->AddUniformTo("Terrain", "uShine");
	ShaderManager::Instance()->AddUniformTo("Terrain", "uDif");
	ShaderManager::Instance()->AddUniformTo("Terrain", "uSpec");
	ShaderManager::Instance()->AddUniformTo("Terrain", "uAmb");
	ShaderManager::Instance()->AddUniformTo("Terrain", "uLightDir");
	ShaderManager::Instance()->AddUniformTo("Terrain", "uPercThroughSeason");
	ShaderManager::Instance()->UseUniform1f("Terrain", "uPercThroughSeason", 0.0f);
	ShaderManager::Instance()->UseUniform1i("Terrain", "texSampler", 0);
	ShaderManager::Instance()->UseUniform4fv("Terrain", "uAmb", amb);
	ShaderManager::Instance()->UseUniform4fv("Terrain", "uDif", dif);
	ShaderManager::Instance()->UseUniform4fv("Terrain", "uSpec", spec);
	ShaderManager::Instance()->UseUniform1f("Terrain", "uShine", shine);
	ShaderManager::Instance()->UnuseProgram("Terrain");

	return true;
}

const void Terrain::Render( const bool sun )
{
	if (sun)
	{
		glPushMatrix();
		glTranslatef(Pos()[0], Pos()[1], Pos()[2]);
		_vbo.BindBuffer();
		BindTexture();
		ShaderManager::Instance()->UseProgram("Terrain");
		ShaderManager::Instance()->UseUniform3fv("Terrain", "uLightDir", Lights::Instance()->GetSunDirection());
		ShaderManager::Instance()->UseUniform1f("Terrain", "uPercThroughSeason", _percThroughSeason);
		_vbo.Render(GL_TRIANGLES);
		ShaderManager::Instance()->UnuseProgram("Terrain");
		UnbindTexture();
		_vbo.UnbindBuffer();
		glPopMatrix();
	}
	else
	{

	}

	glDisable(GL_CULL_FACE);
	_grass.Render(true);
	glEnable(GL_CULL_FACE);
}
