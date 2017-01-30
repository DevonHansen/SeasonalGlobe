#include "ParticleManager.h"
#include <sstream>
using namespace std;

ParticleManager* ParticleManager::_instance = NULL;

ParticleManager::ParticleManager(void)
{
}


ParticleManager::~ParticleManager(void)
{
}

const void ParticleManager::InitAll()
{
	InitShaders();
	vector<string> configLines;
	Utility::Instance()->LoadConfigFile("Resources/Config/Config.txt", configLines);
	map<string,string> returnField;
	Utility::Instance()->ReturnConfigField(returnField, "ParticleManager", configLines);

	int numSystems = atoi(returnField["NumSystems"].c_str());

	for(int i = 0; i < numSystems; ++i)
	{
		ParticleSystem ps;
		stringstream ss;
		ss << i;

		if (returnField[ss.str()] == "Fire")
		{
			ps.Initialize("Resources/Config/FireConfig.txt");
			_fireSystems.push_back(ps);
		}
		else if (returnField[ss.str()] == "Snow")
		{
			ps.Initialize("Resources/Config/SnowConfig.txt");
			_snowSystems.push_back(ps);
		}
		else if (returnField[ss.str()] == "Smoke")
		{
			ps.Initialize("Resources/Config/SmokeConfig.txt");
			_smokeSystems.push_back(ps);
		}
	}

	Utility::Instance()->StringToVector(returnField["Forces"], _forces);
}

const void ParticleManager::InitShaders() const
{
	ShaderManager::Instance()->AddNewShader("Snow",
		"Resources/Shaders/Snow.vert",
		"Resources/Shaders/Snow.frag");
	ShaderManager::Instance()->UseProgram("Snow");
	ShaderManager::Instance()->AddUniformTo("Snow", "uCamPos");
	ShaderManager::Instance()->AddUniformTo("Snow", "uTexture");
	ShaderManager::Instance()->AddUniformTo("Snow", "uScale");
	ShaderManager::Instance()->UnuseProgram("Snow");

	ShaderManager::Instance()->AddNewShader("Fire",
		"Resources/Shaders/Fire.vert",
		"Resources/Shaders/Fire.frag");
	ShaderManager::Instance()->UseProgram("Fire");
	ShaderManager::Instance()->AddUniformTo("Fire", "uCamPos");
	ShaderManager::Instance()->AddUniformTo("Fire", "uTexture");
	ShaderManager::Instance()->AddUniformTo("Fire", "uScale");
	ShaderManager::Instance()->UnuseProgram("Fire");

	ShaderManager::Instance()->AddNewShader("Smoke",
		"Resources/Shaders/Smoke.vert",
		"Resources/Shaders/Smoke.frag");
	ShaderManager::Instance()->UseProgram("Smoke");
	ShaderManager::Instance()->AddUniformTo("Smoke", "uCamPos");
	ShaderManager::Instance()->AddUniformTo("Smoke", "uTexture");
	ShaderManager::Instance()->AddUniformTo("Smoke", "uScale");
	ShaderManager::Instance()->UnuseProgram("Smoke");
}

const void ParticleManager::RenderSmoke( const Vector3f& camPos )
{
	vector<ParticleSystem>::iterator i;
	for(i = _smokeSystems.begin();
		i != _smokeSystems.end();
		++i)
	{
		i->Render(camPos);
	}
}

const void ParticleManager::RenderSnow( const Vector3f& camPos )
{
	vector<ParticleSystem>::iterator i;
	for(i = _snowSystems.begin();
		i != _snowSystems.end();
		++i)
	{
		i->Render(camPos);
	}
}

const void ParticleManager::RenderFire( const Vector3f& camPos )
{
	vector<ParticleSystem>::iterator i;
	for(i = _fireSystems.begin();
		i != _fireSystems.end();
		++i)
	{
		i->Render(camPos);
	}
}

const void ParticleManager::UpdateSmoke( const float dt )
{
	vector<ParticleSystem>::iterator i;
	for(i = _smokeSystems.begin();
		i != _smokeSystems.end();
		++i)
	{
		i->Update(_forces, dt);
	}
}

const void ParticleManager::UpdateSnow( const float dt )
{
	vector<ParticleSystem>::iterator i;
	for(i = _snowSystems.begin();
		i != _snowSystems.end();
		++i)
	{
		i->Update(_forces, dt);
	}
}

const void ParticleManager::UpdateFire( const float dt )
{
	vector<ParticleSystem>::iterator i;
	for(i = _fireSystems.begin();
		i != _fireSystems.end();
		++i)
	{
		i->Update(_forces, dt);
	}
}

const void ParticleManager::StartRender() const
{
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

const void ParticleManager::StopRender() const
{

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glDisable(GL_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
}

const void ParticleManager::ResetSmoke()
{
	for (unsigned int i = 0; i < _smokeSystems.size(); ++i)
	{
		_smokeSystems[i].Reset();
	}
}

const void ParticleManager::ResetSnow()
{
	for (unsigned int i = 0; i < _snowSystems.size(); ++i)
	{
		_snowSystems[i].Reset();
	}
}

const void ParticleManager::ResetFire()
{
	for (unsigned int i = 0; i < _fireSystems.size(); ++i)
	{
		_fireSystems[i].Reset();
	}
}

const void ParticleManager::GetSnowDrifts( vector<Utility::Vertex>& faces )
{
	for (int i = 0; i < _snowSystems.size(); ++i)
	{
		_snowSystems[i].GetSnowDrifts(faces, _forces);
	}
}