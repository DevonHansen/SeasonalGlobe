//////////////////////////////////////////////
// Utility
//--------------------------------------------
// Created By: Devon Hansen
//--------------------------------------------
// Parasoft warnings:
//--------------------------------------------
// Description: Utility methods are put in here. This will be a Singleton class.
#pragma once
#include <vector>
#include <string>
#include <map>
#include "Maths/Vector2f.h"
#include "Maths/Vector3f.h"
#include "Maths/Vector4f.h"
#include "GXBase/include/GXBase.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

class Utility
{
private:
	Utility(void);
	Utility(const Utility&);
	Utility& operator=(const Utility&);

	static Utility* _instance;

public:

	// Struct here due to high amounts of classes using this.
	struct Vertex
	{
		Vector3f _pos;
		Vector2f _tex;
		Vector3f _norm;
		Vector4f _col;
		GLubyte _pad[16];			// Padded for performance
	};

	~Utility(void);

	static Utility* Instance()
	{
		if (_instance == 0)
		{
			_instance = new Utility();
		}

		return _instance;
	}

	const bool LoadConfigFile(const char* filepath, std::vector<std::string>& result);
	const bool ReturnConfigField(std::map<std::string, std::string>& result, const std::string& dataRegion,
		std::vector<std::string>& configFile) const;

	const float RandomFloat(const float a, const float b) const;

	const void* BufferOffset(const int x) const;

	const void StringToVector(const string& s, Vector2f& v);
	const void StringToVector(const string& s, Vector3f& v);
	const void StringToVector(const string& s, Vector4f& v);
};

