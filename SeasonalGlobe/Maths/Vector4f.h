//////////////////////////////////////////////
// Vector4f
//--------------------------------------------
// Created By: Devon Hansen
// On: 13/11/2011
//--------------------------------------------
// Parasoft warnings:
//	- non-const version of operator[] needs to be const. NO. This is a setter.
//--------------------------------------------
// Description: Holds 4 pieces of data and edits them according to
// vector rules

#pragma once
#include <cmath>
#include <iostream>
using namespace std;

class Vector4f
{
private:
	float _data[4];

public:
	explicit Vector4f(float x = 0, float y = 0, float z = 0, float w = 0);
	~Vector4f(void);

	//////////////////////////////////////////
	// Operators (implementation for readable code)
	float& operator[](unsigned int val)
	{
		return const_cast<float&>(const_cast<const Vector4f&>(*this)[val]);
	}

	const float& operator[](unsigned int val) const
	{
		return _data[val];
	}

	Vector4f& operator+=(const Vector4f& rhs)
	{
		Add(*this, rhs);
		return *this;
	}

	Vector4f& operator-=(const Vector4f& rhs)
	{
		Subtract(*this, rhs);
		return *this;
	}

	Vector4f& operator*=(const float rhs)
	{
		MultiByScalar(*this, rhs);
		return *this;
	}

	Vector4f& operator/=(const float rhs)
	{
		DivByScalar(*this, rhs);
		return *this;
	}

	/////////////////////////////////////////
	// Functions ('speedy' versions of operators)
	const void Add(Vector4f& result, const Vector4f& rhs) const
	{
		result[0] = _data[0] + rhs[0];
		result[1] = _data[1] + rhs[1];
		result[2] = _data[2] + rhs[2];
		result[3] = _data[3] + rhs[3];
	}

	const void Subtract(Vector4f& result, const Vector4f& rhs) const
	{
		result[0] = _data[0] - rhs[0];
		result[1] = _data[1] - rhs[1];
		result[2] = _data[2] - rhs[2];
		result[3] = _data[3] - rhs[3];
	}

	const void MultiByScalar(Vector4f& result, const float rhs) const
	{
		result[0] = _data[0] * rhs;
		result[1] = _data[1] * rhs;
		result[2] = _data[2] * rhs;
		result[3] = _data[3] * rhs;
	}

	const void DivByScalar(Vector4f& result, const float rhs) const
	{
		result[0] = _data[0] / rhs;
		result[1] = _data[1] / rhs;
		result[2] = _data[2] / rhs;
		result[3] = _data[3] / rhs;
	}
	
	const void Unit(Vector4f& result) const	// Speedy version
	{
		result /= Length();
	}

	Vector4f Unit() const					// If user hasn't created Vector before-hand
	{
		Vector4f temp = *this;
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

inline ostream& operator<<(ostream& os, Vector4f& v)
{
	return os << '(' << v[0] << ',' << v[1] << ',' << v[2] << ',' << v[3] << ')';
}
inline istream& operator>>(istream& is, Vector4f& v)
{
	char c;

	// in format: (x,y,z,w)
	is >> c >> v[0] >> c >> v[1] >> c >> v[2] >> c >> v[3] >> c;

	return is;
}

inline bool operator==(const Vector4f& lhs, const Vector4f& rhs)
{
	float e = 0.00001f;
	if((lhs[0] >= (rhs[0] - e)) && (lhs[0] <= (rhs[0] + e))) 
		if((lhs[1] >= (rhs[1] - e)) && (lhs[1] <= (rhs[1] + e)))
			if((lhs[2] >= (rhs[2] - e)) && (lhs[2] <= (rhs[2] + e))) 
				if((lhs[3] >= (rhs[3] - e)) && (lhs[3] <= (rhs[3] + e))) 
					return true;
	return false;
}

inline bool operator!=(const Vector4f& lhs, const Vector4f& rhs)
{
	return !(lhs == rhs);
}

inline Vector4f operator+(const Vector4f& lhs, const Vector4f& rhs)
{
	return Vector4f (lhs) += rhs;
}

inline Vector4f operator-(const Vector4f& lhs, const Vector4f& rhs)
{
	return Vector4f (lhs) -= rhs;
}

inline Vector4f operator*(const Vector4f& lhs, const float rhs)
{
	return Vector4f (lhs) *= rhs;
}

inline Vector4f operator*(const float lhs, const Vector4f& rhs)
{
	return Vector4f (rhs) *= lhs;
}

inline Vector4f operator/(const Vector4f& lhs, const float rhs)
{
	return Vector4f (lhs) /= rhs;
}