#include "ParticleSystem.h"
#include "Utility.h"
#include <string>
#include <map>
using namespace std;

ParticleSystem::ParticleSystem(void)
{
}


ParticleSystem::~ParticleSystem(void)
{
}

const void ParticleSystem::Initialize(const char* filepath)
{
	vector<string> configLines;
	Utility::Instance()->LoadConfigFile(filepath, configLines);
	map<string,string> returnVals;
	Utility::Instance()->ReturnConfigField(returnVals, "System", configLines);

	int numFire = atoi(returnVals["NumFireEmitters"].c_str());
	int numSmoke = atoi(returnVals["NumSmokeEmitters"].c_str());
	int numSnow = atoi(returnVals["NumSnowEmitters"].c_str());

	string parseInfo;
	ParticleEmitter* pe;
	for(int i = 0; i < numSmoke; ++i)
	{
		parseInfo = "ESM";
		parseInfo += (49+i);
		Utility::Instance()->ReturnConfigField(returnVals, parseInfo, configLines);
		pe = new ParticleEmitter();
		pe->Initialize("Smoke", returnVals);
		_emitters.push_back(pe);
	}

	for(int i = 0; i < numFire; ++i)
	{
		parseInfo = "EF";
		parseInfo += (49+i);
		Utility::Instance()->ReturnConfigField(returnVals, parseInfo, configLines);
		pe = new ParticleEmitter();
		pe->Initialize("Fire", returnVals);
		_emitters.push_back(pe);
	}	

	for(int i = 0; i < numSnow; ++i)
	{
		parseInfo = "ES";
		parseInfo += (49+i);
		Utility::Instance()->ReturnConfigField(returnVals, parseInfo, configLines);
		pe = new ParticleEmitter();
		pe->Initialize("Snow", returnVals);
		_emitters.push_back(pe);
	}
}

const void ParticleSystem::Render(const Vector3f& camPos)
{
	for(int i = 0; i < _emitters.size(); ++i)
	{
		_emitters[i]->Render(camPos);
	}
}

const void ParticleSystem::Update(const Vector3f& force, const float dt)
{
	for(int i = 0; i < _emitters.size(); ++i)
	{
		_emitters[i]->Update(force, dt);
	}
}

const void ParticleSystem::Reset()
{
	for (int i = 0; i < _emitters.size(); ++i)
	{
		_emitters[i]->Reset();
	}
}

const void ParticleSystem::GetSnowDrifts( vector<Utility::Vertex>& faces, Vector3f& accel )
{
	for (int i = 0; i < _emitters.size(); ++i)
	{
		_emitters[i]->GetSnowDrifts(faces, accel);
	}
}
