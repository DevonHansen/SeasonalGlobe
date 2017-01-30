#pragma once
#include "VBO.h"
#include "Utility.h"
#include "Maths\Vector3f.h"
#include "ShaderManager.h"
#include <vector>
#include "ITexturedShape.h"

class Grass : public ITexturedShape
{
private:
	VBO _vbo;
	vector<Utility::Vertex> _lakeFaces;

	const void RandomPosRot(vector<Utility::Vertex>& faces, const float radius);

public:
	Grass(void)
		: ITexturedShape()
	{}
	~Grass(void);

	const void Initialize();
	const void Render(const bool sun);
	const void LakeFaces(const vector<Utility::Vertex>& faces)
	{
		_lakeFaces = faces;
	}
	/*const void Grow(const float dt);
	const void Die(const float dt);*/
};

