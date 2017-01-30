#pragma once
#include "ShaderManager.h"
#include "ParticleSystem.h"
#include "Utility.h"
#include <map>
#include <string>

class ParticleManager
{
private:
	ParticleManager(void);
	ParticleManager(const ParticleManager&);
	ParticleManager& operator=(const ParticleManager&);

	static ParticleManager* _instance;
	vector<ParticleSystem> _fireSystems;
	vector<ParticleSystem> _smokeSystems;
	vector<ParticleSystem> _snowSystems;

	Vector3f _forces;

	const void InitShaders() const;

public:
	~ParticleManager(void);

	static ParticleManager* Instance()
	{
		if(_instance == 0)
			_instance = new ParticleManager();

		return _instance;
	}

	const void InitAll();

	const void StartRender() const;
	const void StopRender() const;

	const void RenderSmoke(const Vector3f& camPos);
	const void RenderSnow(const Vector3f& camPos);
	const void RenderFire(const Vector3f& camPos);

	const void UpdateSmoke(const float dt);
	const void UpdateSnow(const float dt);
	const void UpdateFire(const float dt);

	const void ResetSmoke();
	const void ResetSnow();
	const void ResetFire();

	const void GetSnowDrifts(vector<Utility::Vertex>& faces);
};

