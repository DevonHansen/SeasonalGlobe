#pragma once
#include "ITexturedShape.h"
#include "Grass.h"
#include "VBO.h"

class Terrain : public ITexturedShape
{
private:
	VBO _vbo;
	float _percThroughSeason;
	Grass _grass;

public:
	explicit Terrain(void)
		: ITexturedShape(), _percThroughSeason(0)
	{}
	~Terrain(void);

	const bool Initialize();
	const void Render(const bool sun);
	const void PercThroughSeason(const float perc)
	{
		_percThroughSeason = perc;
	}
};

