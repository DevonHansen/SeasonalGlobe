//////////////////////////////////////////////
// VBO
//--------------------------------------------
// Created By: Devon Hansen
//--------------------------------------------
// Parasoft warnings:
//--------------------------------------------
// Description: Holds data of a VBO and allows render. 
// Note: Bind and Unbind must be away from Render method so can use Shader
#pragma once
#include <vector>
#include "Utility.h"
#include "GXBase/include/GXBase.h"

class VBO : public glex
{
private:
	GLuint _vboID;
	int _faceSize;

public:
	explicit VBO(void);
	~VBO(void);

	const void CreateVBO(const std::vector<Utility::Vertex>& faces);
	const void BindBuffer();
	const void Render(GLenum type) const;
	const void UnbindBuffer();
};