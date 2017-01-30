#pragma once
#include "ITexturedShape.h"
#include "VBO.h"
class Base : public ITexturedShape
{
private:
	VBO _vbo;

public:
	Base(void)
		: ITexturedShape()
	{}
	~Base(void);

	const bool Initialize();
	const void Render(const bool sun);
};

