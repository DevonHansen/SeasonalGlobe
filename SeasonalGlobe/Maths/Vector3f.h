//////////////////////////////////////////////
// Vector3f
//--------------------------------------------
// Created By: Devon Hansen
// On: 13/11/2011
//--------------------------------------------
// Parasoft warnings:
//	- non-const version of operator[] needs to be const. NO. This is a setter.
//--------------------------------------------
// Description: Holds 3 pieces of data and edits them according to 
// vector rules
#pragma once
#include <cmath>
#include <iostream>
using namespace std;

class Vector3f
{
private:
	float _data[3];

public:
	explicit Vector3f(float x = 0, float y = 0, float z = 0);
	~Vector3f(void);

	//////////////////////////////////////////
	// Operators (implementation for readable code)
	float& operator[](unsigned int val)
	{
		return const_cast<float&>(const_cast<const Vector3f&>(*this)[val]);
	}

	const float& operator[](unsigned int val) const
	{
		return _data[val];
	}

	Vector3f& operator+=(const Vector3f& rhs)
	{
		Add(*this, rhs);
		return *this;
	}

	Vector3f& operator-=(const Vector3f& rhs)
	{
		Subtract(*this, rhs);
		return *this;
	}

	Vector3f& operator*=(const float rhs)
	{
		MultiByScalar(*this, rhs);
		return *this;
	}

	Vector3f& operator/=(const float rhs)
	{
		DivByScalar(*this, rhs);
		return *this;
	}

	/////////////////////////////////////////
	// Functions ('speedy' versions of operators)
	const void Add(Vector3f& result, const Vector3f& rhs) const
	{
		result[0] = _data[0] + rhs[0];
		result[1] = _data[1] + rhs[1];
		result[2] = _data[2] + rhs[2];
	}

	const void Subtract(Vector3f& result, const Vector3f& rhs) const
	{
		result[0] = _data[0] - rhs[0];
		result[1] = _data[1] - rhs[1];
		result[2] = _data[2] - rhs[2];
	}

	const void MultiByScalar(Vector3f& result, const float rhs) const
	{
		result[0] = _data[0] * rhs;
		result[1] = _data[1] * rhs;
		result[2] = _data[2] * rhs;
	}

	const void DivByScalar(Vector3f& result, const float rhs) const
	{
		result[0] = _data[0] / rhs;
		result[1] = _data[1] / rhs;
		result[2] = _data[2] / rhs;
	}

	const void Unit(Vector3f& result) const	// Speedy version
	{
		result /= Length();
	}

	Vector3f Unit() const					// If user hasn't created Vector before-hand
	{
		Vector3f temp = *this;
		temp /= Length();
		return temp;
	}

	const void Normalize()
	{
		*this /= Length();
	}

	const float LengthSquared() const;		// Not inline (CPU intensive)
	const float Length() const;

	const float Dot(const Vector3f& a) const
	{
		return ((_data[0]*a[0]) +
				(_data[1]*a[1]) +
				(_data[2]*a[2]));
	}

	const void Cross(Vector3f& result, const Vector3f& a)
	{
		result[0] = (_data[1]*a[2]) - (_data[2]*a[1]);
		result[1] = (_data[2]*a[0]) - (_data[0]*a[2]);
		result[2] = (_data[0]*a[1]) - (_data[1]*a[0]);
	}
};

inline ostream& operator<<(ostream& os, Vector3f& v)
{
	return os << '(' << v[0] << ',' << v[1] << ',' << v[2] << ')';
}
inline istream& operator>>(istream& is, Vector3f& v)
{
	char c;
	float x,y,z;

	// in format: (x,y,z,w)
	is >> c >> x >> c >> y >> c >> z >> c;

	v[0] = x;
	v[1] = y;
	v[2] = z;

	return is;
}

inline bool operator==(const Vector3f& lhs, const Vector3f& rhs)
{
	float e = 0.00001f;
	if((lhs[0] >= (rhs[0] - e)) && (lhs[0] <= (rhs[0] + e))) 
		if((lhs[1] >= (rhs[1] - e)) && (lhs[1] <= (rhs[1] + e)))
			if((lhs[2] >= (rhs[2] - e)) && (lhs[2] <= (rhs[2] + e))) 
				return true;
	return false;
}

inline bool operator!=(const Vector3f& lhs, const Vector3f& rhs)
{
	return !(lhs == rhs);
}

inline Vector3f operator+(const Vector3f& lhs, const Vector3f& rhs)
{
	return Vector3f (lhs) += rhs;
}

inline Vector3f operator-(const Vector3f& lhs, const Vector3f& rhs)
{
	return Vector3f (lhs) -= rhs;
}

inline Vector3f operator*(const Vector3f& lhs, const float rhs)
{
	return Vector3f (lhs) *= rhs;
}

inline Vector3f operator*(const float lhs, const Vector3f& rhs)
{
	return Vector3f (rhs) *= lhs;
}

inline Vector3f operator/(const Vector3f& lhs, const float rhs)
{
	return Vector3f (lhs) /= rhs;
}