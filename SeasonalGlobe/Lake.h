#pragma once
#include "ITexturedShape.h"
#include "VBO.h"
class Lake : public ITexturedShape
{
private:
	VBO _vbo;

public:
	explicit Lake(void)
		: ITexturedShape()
	{}
	~Lake(void);

	const bool Initialize();
	const void Render(const bool sun);
};

