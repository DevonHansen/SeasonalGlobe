#include "Lights.h"
#include "Utility.h"
#include <vector>
#include <map>
#include <string>
using namespace std;

Lights* Lights::_instance = NULL;

Lights::Lights(void)
	: _type(Sun), _sunFlag(false)
{
}

Lights::~Lights(void)
{
}

const void Lights::CreateLights( const char* filepath )
{
	vector<string> configLines;
	Utility::Instance()->LoadConfigFile(filepath, configLines);

	map<string,string> configData;
	Utility::Instance()->ReturnConfigField(configData, "Sun", configLines);
	Utility::Instance()->StringToVector(configData["Direction"], _sun._direction);
	Utility::Instance()->StringToVector(configData["Colour"], _sun._colour);

	string parseInfo;
	for (int i = 0; i < 4; ++i)
	{
		parseInfo = "SpotLight";
		parseInfo += (49+i);
		Utility::Instance()->ReturnConfigField(configData, parseInfo, configLines);
		Utility::Instance()->StringToVector(configData["Position"], _spot[i]._position);
		Utility::Instance()->StringToVector(configData["Direction"], _spot[i]._direction);
		Utility::Instance()->StringToVector(configData["Colour"], _spot[i]._colour);
	}
}

const void Lights::UpdateSunPosition( const float dt )
{
	Vector3f dir = _sun._direction;

	dir[0] += dt/2.0f;

	if (dir[0] >= 1.0f)
	{
		dir[0] = -1.0f;
		_sunFlag = false;
	}

	if (!_sunFlag)
	{
		dir[1] -= dt/2.0f;

		if (dir[1] <= -1.0f)
		{
			_sunFlag = true;
		}
	}
	else
	{
		dir[1] += dt/2.0f;
	}

	_sun._direction = dir;
}

const void Lights::ReflectLight()
{
	_sun._direction[1] = -_sun._direction[1];
	_sun._direction[2] = -_sun._direction[2];
}
