#pragma once
#include <vector>
#include "VBO.h"
#include "GXBase/include/GXBase.h"
using namespace std;
using namespace gxbase;

class Leaf : public glex
{
public:
	struct LeafMats 
	{
		float _orgMat[16];
		float _curMat[16];
	};

private:
	VBO _vbo;
	std::vector<LeafMats> _mats;
	GLuint _texID;
	int _amountShown;
	float _totalTime;
	float _curTime;
	float _releaseTime;
	int _amountFalling;

	const void BuildVBO();

public:
	Leaf()
		: _texID(0), _amountShown(0), _totalTime(0), _curTime(0),
		_releaseTime(0), _amountFalling(0)
	{}
	~Leaf(void);

	const void Initialize(const vector<LeafMats>& mats, bool allShown, const float timePerSeason);
	const void Render();

	const void Grow(const float dt);
	const void Die(const float dt, const float percSeason);

	const void Reset();
};

