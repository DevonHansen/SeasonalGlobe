#include "Lightening.h"
#include "ShaderManager.h"
#include <vector>
#include <string>
#include <map>
using namespace std;

const bool Lightening::Initialize(const Vector3f& treeBase)
{
	vector<Utility::Vertex> faces;

	Utility::Vertex temp;
	temp._pos[0] = 0.0f;
	temp._pos[1] = 1.0f;
	temp._pos[2] = 0.0f;

	faces.push_back(temp);

	temp._pos[0] = -0.1f;
	temp._pos[1] = 0.7f;
	faces.push_back(temp);

	temp._pos[0] = 0.1f;
	temp._pos[1] = 0.4f;
	faces.push_back(temp);

	temp._pos = treeBase;
	faces.push_back(temp);

	_vbo.CreateVBO(faces);

	ShaderManager::Instance()->AddNewShader("Lightening", 
		"Resources/Shaders/Lightening.vert",
		"Resources/Shaders/Lightening.frag");
	ShaderManager::Instance()->UseProgram("Lightening");
	ShaderManager::Instance()->AddAttribTo("Lightening", "aVertex", 3, 0);
	ShaderManager::Instance()->UnuseProgram("Lightening");

	return true;
}

const void Lightening::Render()
{
	if (_flickOn)
	{
		glPushMatrix();
		_vbo.BindBuffer();
		ShaderManager::Instance()->UseProgram("Lightening");
		_vbo.Render(GL_LINE_STRIP);
		ShaderManager::Instance()->UnuseProgram("Lightening");
		_vbo.UnbindBuffer();
		glPopMatrix();
		_flickOn = false;
	}
	else
	{
		_flickOn = true;
	}
	
}