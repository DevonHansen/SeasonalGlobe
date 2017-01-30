#pragma once
#include "ITexturedShape.h"
#include "VBO.h"
class House : public ITexturedShape
{
private:
	VBO _vbo;
	float _percThroughSeason;

public:
	House(void)
		: ITexturedShape(), _percThroughSeason(0)
	{}
	~House(void);

	const bool Initialize();
	const void Render(const bool sun);
	const void PercThroughSeason(const float perc)
	{
		_percThroughSeason = perc;
	}
	const void ReducePercThroughSeason(const float reduce)
	{
		if (_percThroughSeason > 0.0f)
		{
			_percThroughSeason -= reduce;
		}
	}
};

