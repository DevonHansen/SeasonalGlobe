#pragma once
#include "VBO.h"
#include "Maths/Vector3f.h"

class Lightening
{
private:
	VBO _vbo;
	bool _flickOn;

public:
	Lightening(void)
		: _flickOn(false)
	{}
	~Lightening(void){}

	const bool Initialize(const Vector3f& treeBase);
	const void Render();
};