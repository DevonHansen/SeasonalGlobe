#pragma once
#include <vector>
#include <ctime>
#include "VBO.h"
#include "Leaf.h"
#include "Maths/Vector3f.h"
#include "GXBase/include/GXBase.h"
class Branches : public glex
{
private:
	enum RenderMode
	{
		Wireframe,
		NonSmooth,
		Smooth,
		Textured
	};

	struct Branch
	{
		GLfloat _matrix[16];
		int _level;
		float _scale;
	};

	vector<Branch> _branches;
	vector<Leaf::LeafMats> _leaves;
	VBO _vbo;
	GLuint _texID;

	Vector3f _position;
	long _treeSeed;
	int _iterations;
	int _levelToGrow;
	float _growRate;
	char* _shaderName;

	RenderMode _curMode;

	const void Fractal(int level);

public:
	explicit Branches(void)
		: _texID(0), _position(Vector3f()), _treeSeed(long(time(NULL))), _iterations(0), 
		_levelToGrow(0), _growRate(0), _shaderName(""), _curMode(Wireframe)
	{}
	~Branches(void);

	const bool Initialize();
	const void Render();
	const void Grow(const float dt);
	const void Shrink(const float dt);

	const void UpdateRenderMode();
	const vector<Leaf::LeafMats>& GetLeafMats() const
	{
		return _leaves;
	}
};