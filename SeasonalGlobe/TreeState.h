#pragma once
#include "Branches.h"
#include "Leaf.h"
#include "ParticleManager.h"
#include "Lightening.h"

class TreeState
{
private:
	enum State
	{
		Branch_Grow,
		Leaf_Grow,
		Leaf_Die,
		Branch_Die,
		None
	};

	State _currentState;
	Branches _branches;
	Leaf _leaves;
	Lightening _lightening;
	Vector3f _position;

	float _lighteningLife;
	float _curTime;

public:
	TreeState(void);
	~TreeState(void);

	const bool Initialize();
	const void Render(const Vector3f& camPos);
	const void Update(const float dt, const float percSeason);

	const void NextState()
	{
		switch(_currentState)
		{
		case Branch_Grow:
			_currentState = Leaf_Grow;
			break;
		case Leaf_Grow:
			_currentState = Leaf_Die;
			break;
		case Leaf_Die:
			_currentState = Branch_Die;
			break;
		case Branch_Die:
			_leaves.Reset();
			_curTime = 0;
			_currentState = None;
			break;
		case None:
			_currentState = Branch_Grow;
			ParticleManager::Instance()->ResetFire();
			break;
		}
	}

	const void NextRenderState()
	{
		_branches.UpdateRenderMode();
	}
};

