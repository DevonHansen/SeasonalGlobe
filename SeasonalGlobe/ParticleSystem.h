#pragma once
#include <vector>
#include "ParticleEmitter.h"

class ParticleSystem
{
private:
	std::vector<ParticleEmitter*> _emitters;

public:
	explicit ParticleSystem(void);
	~ParticleSystem(void);

	const void Initialize(const char* filepath);
	const void Render(const Vector3f& camPos);
	const void Update(const Vector3f& force, const float dt);
	const void Reset();

	const void GetSnowDrifts(vector<Utility::Vertex>& faces, Vector3f& accel);
};

