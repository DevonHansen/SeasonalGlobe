#include "Vector3f.h"

Vector3f::Vector3f(float x, float y, float z)
{
	_data[0] = x;
	_data[1] = y;
	_data[2] = z;
}

const float Vector3f::LengthSquared() const
{
	return ((_data[0]*_data[0]) +
		(_data[1]*_data[1]) +
		(_data[2]*_data[2]));
}

const float Vector3f::Length() const
{
	return sqrtf(LengthSquared());
}

Vector3f::~Vector3f(void)
{
}
