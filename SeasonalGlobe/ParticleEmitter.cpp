#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter(void)
	: _textureID(0), _maxParticles(0), _curParticles(0), _release(0), _curTime(0),
	_shaderName(""), _scale(0)
{
}

ParticleEmitter::~ParticleEmitter(void)
{
}

const void ParticleEmitter::Initialize(char* shader, map<string,string>& configLines)
{
	_shaderName = shader;
	_maxParticles = atoi(configLines["NumOfParticles"].c_str());

	Utility::Instance()->StringToVector(configLines["Position"], _emitterPos);

	Vector3f minPos, maxPos;
	Utility::Instance()->StringToVector(configLines["MinPos"], minPos);
	Utility::Instance()->StringToVector(configLines["MaxPos"], maxPos);

	Vector3f minVel, maxVel;
	Utility::Instance()->StringToVector(configLines["MinVel"], minVel);
	Utility::Instance()->StringToVector(configLines["MaxVel"], maxVel);

	Utility::Instance()->StringToVector(configLines["ForceScale"], _forceFeedback);

	_release = (float)atof(configLines["ReleaseTime"].c_str());

	float minTTL = (float)atof(configLines["MinTTL"].c_str());
	float maxTTL = (float)atof(configLines["MaxTTL"].c_str());

	_scale = (float)atof(configLines["Scale"].c_str());

	string texturePath = configLines["Texture"];

	Particle temp;
	for(int i = 0; i < _maxParticles; ++i)
	{
		temp._orgPosition = temp._postion = RandomVector(minPos, maxPos);
		temp._orgVelocity = temp._velocity = RandomVector(minVel, maxVel);
		temp._ttl[0] = temp._ttl[1] = Utility::Instance()->RandomFloat(minTTL, maxTTL);
		_particles.push_back(temp);
	}

	Image texture;
	texture.Load(texturePath.c_str());
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	texture.gluBuild2DMipmaps();
	texture.Free();
	glBindTexture(GL_TEXTURE_2D, 0);
}

const void ParticleEmitter::Render(const Vector3f& camPos)
{
	glPushMatrix();
	glTranslatef(_emitterPos[0],_emitterPos[1],_emitterPos[2]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glActiveTexture(GL_TEXTURE0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(4, GL_FLOAT, sizeof(Particle), &(_particles[0]._postion));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Particle), &(_particles[0]._ttl));
	ShaderManager::Instance()->UseProgram(_shaderName);
	ShaderManager::Instance()->UseUniform1f(_shaderName, "uScale", _scale);
	ShaderManager::Instance()->UseUniform3fv(_shaderName, "uCamPos", camPos);
	ShaderManager::Instance()->UseUniform1i(_shaderName, "uTexture", 0);
	glDrawArrays(GL_POINTS, 0, _curParticles);
	ShaderManager::Instance()->UnuseProgram(_shaderName);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();
}

const void ParticleEmitter::Update(const Vector3f& force, const float dt)
{
	_curTime += dt;
	Vector4f vec4Force = Vector4f(force[0]*_forceFeedback[0], force[1]*_forceFeedback[1], force[2]*_forceFeedback[2], 1.0);

	if(_shaderName == "Snow")
	{
		// No need for TTL update
		for(int i = 0; i < _curParticles; ++i)
		{
			if((_particles[i]._postion[1] + _emitterPos[1]) <= 0.0f)
			{
				//Reset
				_particles[i]._postion = _particles[i]._orgPosition;
				_particles[i]._velocity = _particles[i]._orgVelocity;
			}
			else
			{
				// Update velocity (a = ms^-2, v = ms^-1)
				// So new v = (a*t) + old v
				_particles[i]._velocity += (vec4Force * dt);
				_particles[i]._velocity[3] = 1.0f;
				//Update Position (p = m, v = ms^-1)
				// So new p = (v*t) + old p
				_particles[i]._postion += (_particles[i]._velocity*dt);
				_particles[i]._postion[3] = 1.0f;
			}
		}

		if((_curTime >= _release) && (_curParticles < _maxParticles))
		{
			_curTime = 0.0f;
			++_curParticles;
		}
	}
	else
	{
		// Org TTL = 0, Cur TTL = 1
		for(int i = 0; i < _curParticles; ++i)
		{
			if(_particles[i]._ttl[1] <= 0.0f)
			{
				//Reset
				_particles[i]._postion = _particles[i]._orgPosition;
				_particles[i]._velocity = _particles[i]._orgVelocity;
				_particles[i]._ttl[1] = _particles[i]._ttl[0];
			}
			else
			{
				// Update velocity (a = ms^-2, v = ms^-1)
				// So new v = (a*t) + old v
				_particles[i]._velocity += (vec4Force * dt);
				_particles[i]._velocity[3] = 1.0f;
				//Update Position (p = m, v = ms^-1)
				// So new p = (v*t) + old p
				_particles[i]._postion += (_particles[i]._velocity*dt);
				_particles[i]._postion[3] = 1.0f;

				_particles[i]._ttl[1] -= dt;
			}
		}

		if((_curTime >= _release) && (_curParticles < _maxParticles))
		{
			_curTime = 0.0f;
			++_curParticles;
		}
	}
}

Vector4f ParticleEmitter::RandomVector(const Vector3f& min, const Vector3f& max) const
{
	return Vector4f(Utility::Instance()->RandomFloat(min[0],max[0]),
		Utility::Instance()->RandomFloat(min[1],max[1]),
		Utility::Instance()->RandomFloat(min[2],max[2]), 1.0f);
}

const void ParticleEmitter::Reset()
{
	_curParticles = 0;

	for(unsigned int i = 0; i < _particles.size(); ++i)
	{
		_particles[i]._postion = _particles[i]._orgPosition;
		_particles[i]._velocity = _particles[i]._orgVelocity;
		_particles[i]._ttl[1] = _particles[i]._ttl[0];
	}
}

const void ParticleEmitter::GetSnowDrifts( vector<Utility::Vertex>& faces, Vector3f& accel )
{
	if(_shaderName == "Snow")
	{
		// Using the equation s = ut + 1/2at^2 we can calculate t...
		// t = sqrt(2s/a)
		// And this can be placed back into the equation giving us...
		// s = 1/2a(sqrt(2s/a))^2
		// Find all landing positions that are relevant
		vector<Vector3f> relevantParticles;

		for (int i = 0; i < _particles.size(); ++i)
		{
			float displacement = -1;
			float timeTaken = sqrt((2*displacement)/accel[1]);

			float finalXPos = _particles[i]._orgPosition[0] + (((accel[0]*_forceFeedback[0])*(timeTaken*timeTaken))/2.0f);
			float finalZPos = _particles[i]._orgPosition[2] + (((accel[2]*_forceFeedback[2])*(timeTaken*timeTaken))/2.0f);
			
			if(sqrt((finalXPos*finalXPos) + (finalZPos*finalZPos)) > 0.8f)
				continue;

			relevantParticles.push_back(Vector3f(finalXPos,0,finalZPos));
		}

		// Loop through all the faces, then particle positions, to add
		// them to colour value (used for displacement)
		for (int i = 0; i < faces.size(); ++i)
		{
			for (int j = 0; j < relevantParticles.size(); ++j)
			{
				if (relevantParticles[j][0] >= (faces[i]._pos[0] - 0.05f) &&
					relevantParticles[j][0] <= (faces[i]._pos[0] + 0.05f) )
				{
					if (relevantParticles[j][2] >= (faces[i]._pos[2] - 0.05f) &&
						relevantParticles[j][2] <= (faces[i]._pos[2] + 0.05f) )
					{
						faces[i]._col[0] += 1;
					}
				}
			}
		}
	}
}
