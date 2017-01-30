#include "Vector4f.h"


Vector4f::Vector4f(float x, float y, float z, float w)
{
	_data[0] = x;
	_data[1] = y;
	_data[2] = z;
	_data[3] = w;
}

const float Vector4f::LengthSquared() const
{
	return ((_data[0]*_data[0]) +
			(_data[1]*_data[1]) +
			(_data[2]*_data[2]) +
			(_data[3]*_data[3]));
}

const float Vector4f::Length() const
{
	return sqrtf(LengthSquared());
}

Vector4f::~Vector4f(void)
{
}
