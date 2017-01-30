#include "Grass.h"

const void Grass::Initialize()
{
	Utility::Vertex v;
	vector<Utility::Vertex> faces;

	for(int i = 0; i < 1000; ++i)
	{
		// Bottom Left Corner
		v._pos[0] = -0.03f;
		v._pos[1] = 0;
		v._pos[2] = 0;
		v._tex[0] = 0;
		v._tex[1] = 0;
		faces.push_back(v);

		// Top Left Corner
		v._pos[0] = -0.03f;
		v._pos[1] = 0.02f;
		v._pos[2] = 0;
		v._tex[0] = 0;
		v._tex[1] = 1;
		faces.push_back(v);

		// Bottom Right Corner
		v._pos[0] = 0.03f;
		v._pos[1] = 0;
		v._pos[2] = 0;
		v._tex[0] = 1;
		v._tex[1] = 0;
		faces.push_back(v);

		faces.push_back(v);

		// Top Left Corner
		v._pos[0] = -0.03f;
		v._pos[1] = 0.02f;
		v._pos[2] = 0;
		v._tex[0] = 0;
		v._tex[1] = 1;
		faces.push_back(v);

		// Top Right Corner
		v._pos[0] = 0.03f;
		v._pos[1] = 0.02f;
		v._pos[2] = 0;
		v._tex[0] = 1;
		v._tex[1] = 1;
		faces.push_back(v);

		//////////////////////////////////////////////////////////////////////////
		// Next square
		// Bottom Left Corner
		v._pos[2] = -0.03f;
		v._pos[1] = 0;
		v._pos[0] = 0;
		v._tex[0] = 0;
		v._tex[1] = 0;
		faces.push_back(v);

		// Top Left Corner
		v._pos[2] = -0.03f;
		v._pos[1] = 0.02f;
		v._pos[0] = 0;
		v._tex[0] = 0;
		v._tex[1] = 1;
		faces.push_back(v);

		// Bottom Right Corner
		v._pos[2] = 0.03f;
		v._pos[1] = 0;
		v._pos[0] = 0;
		v._tex[0] = 1;
		v._tex[1] = 0;
		faces.push_back(v);

		faces.push_back(v);

		// Top Left Corner
		v._pos[2] = -0.03f;
		v._pos[1] = 0.02f;
		v._pos[0] = 0;
		v._tex[0] = 0;
		v._tex[1] = 1;
		faces.push_back(v);

		// Top Right Corner
		v._pos[2] = 0.03f;
		v._pos[1] = 0.02f;
		v._pos[0] = 0;
		v._tex[0] = 1;
		v._tex[1] = 1;
		faces.push_back(v);
	}

	RandomPosRot(faces, 0.8f);

	_vbo.CreateVBO(faces);

	InitializeTexture("Resources/Textures/grassBlade.tga");

	// Create Shaders
	ShaderManager::Instance()->AddNewShader("Grass",
		"Resources/Shaders/Grass.vert",
		"Resources/Shaders/Grass.frag");
	ShaderManager::Instance()->UseProgram("Grass");
	ShaderManager::Instance()->AddAttribTo("Grass", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("Grass", "aTexCoords", 2, 12);
	ShaderManager::Instance()->AddAttribTo("Grass", "aPosition", 3, 20);
	ShaderManager::Instance()->AddUniformTo("Grass", "uTexture");
	ShaderManager::Instance()->UseUniform1i("Grass", "uTexture", 0);
	ShaderManager::Instance()->UnuseProgram("Grass");
}

const void Grass::RandomPosRot(vector<Utility::Vertex>& faces, const float radius)
{
	for(int i = 0; i < faces.size(); ++i)
	{
		float length = Utility::Instance()->RandomFloat(0, 1);
		float angle = Utility::Instance()->RandomFloat(0, 360);

		float x = cos(angle) * (sqrt(length*radius));
		float z = sin(angle) * (sqrt(length*radius));

		bool inLake = false;
		int test = 0;
		for (int j = 0; j < _lakeFaces.size(); ++j)
		{
			// Within X vertex
			if ((x >= (_lakeFaces[j]._pos[0] - 0.05f)) &&
				(x <= (_lakeFaces[j]._pos[0] + 0.05f)))
			{
				// Within Y vertex
				if ((z >= (_lakeFaces[j]._pos[2] - 0.05f)) &&
					(z <= (_lakeFaces[j]._pos[2] + 0.05f)))
				{
					if (_lakeFaces[j]._pos[1] < 0.0f)
					{
						inLake = true;
						break;
					}
				}
			}
		}

		if(!inLake)
		{
			faces[i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;

			faces[++i]._norm[0] = x;
			faces[i]._norm[1] = z;
		}
		else
		{
			--i;
		}
	}
}

const void Grass::Render(const bool sun)
{
	glDepthMask(GL_FALSE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPushMatrix();
	_vbo.BindBuffer();
	BindTexture();
	ShaderManager::Instance()->UseProgram("Grass");
	_vbo.Render(GL_TRIANGLES);
	UnbindTexture();
	ShaderManager::Instance()->UnuseProgram("Grass");
	_vbo.UnbindBuffer();
	glPopMatrix();
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
}

Grass::~Grass(void)
{
}
