//////////////////////////////////////////////
// Vector2f
//--------------------------------------------
// Created By: Devon Hansen
// On: 13/11/2011
//--------------------------------------------
// Parasoft warnings:
//	- non-const version of operator[] needs to be const. NO. This is a setter.
//--------------------------------------------
// Description: Holds 2 pieces of data and edits them according to 
// vector rules
#pragma once
#include <cmath>
#include <iostream>
using namespace std;

class Vector2f
{
private:
	float _data[2];

public:
	explicit Vector2f(float x = 0, float y = 0);
	~Vector2f(void);

	//////////////////////////////////////////
	// Operators (implementation for readable code)
	float& operator[](unsigned int val)
	{
		return const_cast<float&>(const_cast<const Vector2f&>(*this)[val]);
	}

	const float& operator[](unsigned int val) const
	{
		return _data[val];
	}

	Vector2f& operator+=(const Vector2f& rhs)
	{
		Add(*this, rhs);
		return *this;
	}

	Vector2f& operator-=(const Vector2f& rhs)
	{
		Subtract(*this, rhs);
		return *this;
	}

	Vector2f& operator*=(const float rhs)
	{
		MultiByScalar(*this, rhs);
		return *this;
	}

	Vector2f& operator/=(const float rhs)
	{
		DivByScalar(*this, rhs);
		return *this;
	}

	/////////////////////////////////////////
	// Functions ('speedy' versions of operators)
	const void Add(Vector2f& result, const Vector2f& rhs) const
	{
		result[0] = _data[0] + rhs[0];
		result[1] = _data[1] + rhs[1];
	}

	const void Subtract(Vector2f& result, const Vector2f& rhs) const
	{
		result[0] = _data[0] - rhs[0];
		result[1] = _data[1] - rhs[1];
	}

	const void MultiByScalar(Vector2f& result, const float rhs) const
	{
		result[0] = _data[0] * rhs;
		result[1] = _data[1] * rhs;
	}

	const void DivByScalar(Vector2f& result, const float rhs) const
	{
		result[0] = _data[0] / rhs;
		result[1] = _data[1] / rhs;
	}

	const void Unit(Vector2f& result) const	// Speedy version
	{
		result /= Length();
	}

	Vector2f Unit() const					// If user hasn't created Vector before-hand
	{
		Vector2f temp = *this;
		temp /= Length();
		return temp;
	}

	const void Normalize()
	{
		*this /= Length();
	}

	const float LengthSquared() const;		// Not inline (CPU intensive)
	const float Length() const;
};

inline const bool FPEquality(const float a, const float b)
{
	float e = 0.00001f;

	if((a >= (b - e)) || (a <= (b + e)))
		return true;

	return false;
}

inline ostream& operator<<(ostream& os, Vector2f& v)
{
	return os << '(' << v[0] << ',' << v[1] << ',' << v[2] << ')';
}
inline istream& operator>>(istream& is, Vector2f& v)
{
	char c;
	float x,y;

	// in format: (x,y,z,w)
	is >> c >> x >> c >> y >> c;

	v[0] = x;
	v[1] = y;

	return is;
}

inline bool operator==(const Vector2f& lhs, const Vector2f& rhs)
{
	float e = 0.00001f;
	if((lhs[0] >= (rhs[0] - e)) && (lhs[0] <= (rhs[0] + e))) 
	{
		if((lhs[1] >= (rhs[1] - e)) && (lhs[1] <= (rhs[1] + e))) 
			return true;
	}

	return false;
	/*return ((FPEquality(lhs[0], rhs[0])) &&
		(FPEquality(lhs[1],rhs[1])));*/
}

inline bool operator!=(const Vector2f& lhs, const Vector2f& rhs)
{
	return !(lhs == rhs);
}

inline Vector2f operator+(const Vector2f& lhs, const Vector2f& rhs)
{
	return Vector2f (lhs) += rhs;
}

inline Vector2f operator-(const Vector2f& lhs, const Vector2f& rhs)
{
	return Vector2f (lhs) -= rhs;
}

inline Vector2f operator*(const Vector2f& lhs, const float rhs)
{
	return Vector2f (lhs) *= rhs;
}

inline Vector2f operator*(const float lhs, const Vector2f& rhs)
{
	return Vector2f (rhs) *= lhs;
}

inline Vector2f operator/(const Vector2f& lhs, const float rhs)
{
	return Vector2f (lhs) /= rhs;
}