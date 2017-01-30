//////////////////////////////////////////////
// OBJLoader
//--------------------------------------------
// Created By: Devon Hansen
//--------------------------------------------
// Parasoft warnings:
//--------------------------------------------
// Description: Loads in a given OBJ file and returns the faces (in a 
// vector of Vertex's)
// Singleton due to not needing to a separate entity per object, just clear
// the vectors of previous data

#pragma once
#include "Utility.h"
#include <vector>
#include <string>
#include "Maths/Vector2f.h"
#include "Maths/Vector3f.h"

#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

class OBJLoader
{
private:
	std::vector<std::string> _fileLines;
	std::vector<Vector3f> _vertices;
	std::vector<Vector3f> _normals;
	std::vector<Vector2f> _textureCoords;

#ifdef _DEBUG
	bool _debugLineFlag;		// Stops mass re-print of debug lines
#endif // _DEBUG

	const bool LoadFile(const char* filepath);

	OBJLoader(const OBJLoader&);
	OBJLoader& operator=(const OBJLoader&);

public:
	explicit OBJLoader(void);
	~OBJLoader(void);

	const bool LoadFaces(const char* filepath, std::vector<Utility::Vertex>& result);

	const void Destroy()
	{
		_fileLines.clear();
		_vertices.clear();
		_normals.clear();
		_textureCoords.clear();
	}
};

