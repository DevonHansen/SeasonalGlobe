#pragma once
#include "ShaderManager.h"
#include "Utility.h"
#include "GXBase\include\GXBase.h"
#include <vector>
#include <map>
#include <string>
using namespace gxbase;
class ParticleEmitter : public glex
{
private:
	struct Particle
	{
		Vector4f _postion, _orgPosition;
		Vector4f _velocity, _orgVelocity;		// Done as 4d vector so easier to add to position
		Vector2f _ttl;							// Done as 2d vector to pass into shader as tex coords (not using them after all)
	};

	vector<Particle> _particles;

	GLuint _textureID;
	int _maxParticles;
	int _curParticles;
	float _release;
	float _curTime;
	char* _shaderName;
	Vector3f _emitterPos;
	Vector3f _forceFeedback;
	float _scale;

	Vector4f RandomVector(const Vector3f& min, const Vector3f& max) const;

public:
	explicit ParticleEmitter(void);
	~ParticleEmitter(void);

	const void Initialize(char* shader, map<string,string>& configLines);
	const void Render(const Vector3f& camPos);
	const void Update(const Vector3f& force, const float dt);
	const void Reset();

	const void GetSnowDrifts(vector<Utility::Vertex>& faces, Vector3f& accel);
};

