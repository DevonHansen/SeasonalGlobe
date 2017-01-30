#pragma once
#include "Base.h"
#include "Globe.h"
#include "House.h"
#include "Lake.h"
#include "TreeState.h"
#include "ParticleManager.h"
#include "Terrain.h"

class World
{
private:
	enum Season
	{
		Spring,
		Summer,
		Autumn,
		Winter
	};

	Season _curSeason;
	Base _base;
	Globe _globe;
	House _house;
	Lake _lake;
	Terrain _terrain;
	TreeState _tree;

	float _curTime;
	float _timePerSeason;

	const void UpdateSeason()
	{
		if(_curSeason == Winter)
		{
			_curSeason = Spring;
		}
		else if (_curSeason == Spring)
		{
			_curSeason = Summer;
		}
		else if(_curSeason == Summer)
		{
			_curSeason = Autumn;
		}
		else if (_curSeason == Autumn)
		{
			_curSeason = Winter;
		}
	}

public:
	explicit World(void);
	~World(void);

	const bool CreateWorld();
	const void Render(const bool insideGlobe, const Vector3f& camPos);
	const void Update(const float dt);
	const void UpdateRenderMode()
	{
		_tree.NextRenderState();
	}
};

