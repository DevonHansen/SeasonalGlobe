#pragma once
#include "IShape.h"
#include "VBO.h"
class Globe :
	public IShape
{
private:
	VBO _vbo;

public:
	Globe(void)
		: IShape()
	{}
	~Globe(void);

	const bool Initialize();
	const void Render(const bool sun);
};

