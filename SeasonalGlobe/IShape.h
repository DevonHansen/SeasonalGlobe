#pragma once
#include "Maths/Vector3f.h"
#include "GXBase/include/GXBase.h"
using namespace gxbase;

class IShape : public glex
{
private:
	Vector3f _pos;
	Vector3f _size;
	Vector3f _rotation;
	
public:
	explicit IShape(const Vector3f& pos = Vector3f(), 
		const Vector3f& size = Vector3f(), 
		const Vector3f& rotation = Vector3f())
		: _pos(pos), _size(size), _rotation(rotation)
	{}
	
	virtual ~IShape(void) {}

	//////////////////////////////////////////////////////////////////////////
	// Pure virtual
	virtual const void Render(const bool sun) = 0;

	const Vector3f& Size() const { return _size; }
	void Size(const Vector3f& val) { _size = val; }

	const Vector3f& Rotation() const { return _rotation; }
	void Rotation(const Vector3f& val) { _rotation = val; }

	const Vector3f& Pos() const { return _pos; }
	void Pos(const Vector3f& val) { _pos = val; }
};