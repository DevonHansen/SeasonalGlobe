#pragma once
#include "Maths/Vector3f.h"
#include "Maths/Vector4f.h"

class Lights
{
public:
	enum LightType
	{
		Sun,
		Spot
	};

private:
	struct Light
	{
		Vector3f _position;
		Vector3f _direction;
		Vector4f _colour;
	};

	Light _sun;
	Light _spot[4];

	Lights(void);
	Lights(const Lights&);
	Lights& operator=(const Lights&);

	static Lights* _instance;

	LightType _type;
	bool _sunFlag;

public:
	~Lights(void);

	static Lights* Instance()
	{
		if(_instance == 0)
			_instance = new Lights();

		return _instance;
	}

	const void CreateLights(const char* filepath);
	const void UpdateSunPosition(const float dt);

	const Vector3f GetSunDirection() const { return _sun._direction; }
	const Vector4f GetSunColour() const { return _sun._colour; }

	const Vector3f GetSpotPosition(const int i) const { return _spot[i]._position; }
	const Vector3f GetSpotDirection(const int i) const { return _spot[i]._direction; }
	const Vector4f GetSpotColour(const int i) const { return _spot[i]._colour; }

	const Lights::LightType Type() const { return _type; }
	const void Type(const Lights::LightType val) { _type = val; }

	const void ReflectLight();
};

