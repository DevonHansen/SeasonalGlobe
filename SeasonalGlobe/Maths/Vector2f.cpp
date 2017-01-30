#include "Vector2f.h"

Vector2f::Vector2f(float x, float y)
{
	_data[0] = x;
	_data[1] = y;
}

const float Vector2f::LengthSquared() const
{
	return ((_data[0]*_data[0]) +
		(_data[1]*_data[1]));
}

const float Vector2f::Length() const
{
	return sqrtf(LengthSquared());
}

Vector2f::~Vector2f(void)
{
}
