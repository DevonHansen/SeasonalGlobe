#include "Branches.h"
#include "ShaderManager.h"
#include "Lights.h"
#include "Utility.h"
#include "OBJLoader.h"
using namespace gxbase;

Branches::~Branches(void)
{
}

const bool Branches::Initialize()
{
	vector<string> configLines;
	if(!Utility::Instance()->LoadConfigFile("Resources/Config/Config.txt", configLines))
		return false;

	map<string,string> configData;
	if(!Utility::Instance()->ReturnConfigField(configData, "Tree", configLines))
		return false;

	OBJLoader obj;
	vector<Utility::Vertex> faces;
	if(!obj.LoadFaces(configData["OBJFile"].c_str(), faces))
		return false;

	_vbo.CreateVBO(faces);

	Utility::Instance()->StringToVector(configData["Position"], _position);

	Vector4f amb, dif, spec;
	float shine;

	Utility::Instance()->StringToVector(configData["Ambience"], amb);
	Utility::Instance()->StringToVector(configData["Diffuse"], dif);
	Utility::Instance()->StringToVector(configData["Specular"], spec);
	shine = (float)atof(configData["Shine"].c_str());

	Image texture;
	texture.Load(configData["TextureFile"].c_str());
	glGenTextures(1, &_texID);
	glBindTexture(GL_TEXTURE_2D, _texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	texture.gluBuild2DMipmaps();
	texture.Free();
	glBindTexture(GL_TEXTURE_2D, 0);

	ShaderManager::Instance()->AddNewShader("TreeNone",
		"Resources/Shaders/TreeNone.vert",
		"Resources/Shaders/TreeNone.frag");
	ShaderManager::Instance()->UseProgram("TreeNone");
	ShaderManager::Instance()->AddAttribTo("TreeNone", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("TreeNone", "aNormal", 3, 20);
	ShaderManager::Instance()->UnuseProgram("TreeNone");

	ShaderManager::Instance()->AddNewShader("TreeSmooth", 
		"Resources/Shaders/TreeSmooth.vert",
		"Resources/Shaders/TreeSmooth.frag");
	ShaderManager::Instance()->UseProgram("TreeSmooth");
	ShaderManager::Instance()->AddAttribTo("TreeSmooth", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("TreeSmooth", "aNormal", 3, 20);
	ShaderManager::Instance()->AddUniformTo("TreeSmooth", "uShine");
	ShaderManager::Instance()->AddUniformTo("TreeSmooth", "uDif");
	ShaderManager::Instance()->AddUniformTo("TreeSmooth", "uSpec");
	ShaderManager::Instance()->AddUniformTo("TreeSmooth", "uAmb");
	ShaderManager::Instance()->AddUniformTo("TreeSmooth", "uLightDir");
	ShaderManager::Instance()->AddUniformTo("TreeSmooth", "uScale");
	ShaderManager::Instance()->AddUniformTo("TreeSmooth", "uPos");
	ShaderManager::Instance()->AddUniformTo("TreeSmooth", "uRot");
	ShaderManager::Instance()->UseUniform4fv("TreeSmooth", "uAmb", amb);
	ShaderManager::Instance()->UseUniform4fv("TreeSmooth", "uDif", dif);
	ShaderManager::Instance()->UseUniform4fv("TreeSmooth", "uSpec", spec);
	ShaderManager::Instance()->UseUniform1f("TreeSmooth", "uShine", shine);
	ShaderManager::Instance()->UnuseProgram("TreeSmooth");

	ShaderManager::Instance()->AddNewShader("TreeTextured", 
		"Resources/Shaders/TreeTextured.vert",
		"Resources/Shaders/TreeTextured.frag");
	ShaderManager::Instance()->UseProgram("TreeTextured");
	ShaderManager::Instance()->AddAttribTo("TreeTextured", "aTexCoord", 2, 12);
	ShaderManager::Instance()->AddAttribTo("TreeTextured", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("TreeTextured", "aNormal", 3, 20);
	ShaderManager::Instance()->AddUniformTo("TreeTextured", "uTexture");
	ShaderManager::Instance()->AddUniformTo("TreeTextured", "uShine");
	ShaderManager::Instance()->AddUniformTo("TreeTextured", "uDif");
	ShaderManager::Instance()->AddUniformTo("TreeTextured", "uSpec");
	ShaderManager::Instance()->AddUniformTo("TreeTextured", "uAmb");
	ShaderManager::Instance()->AddUniformTo("TreeTextured", "uLightDir");
	ShaderManager::Instance()->AddUniformTo("TreeTextured", "uScale");
	ShaderManager::Instance()->AddUniformTo("TreeTextured", "uPos");
	ShaderManager::Instance()->AddUniformTo("TreeTextured", "uRot");
	ShaderManager::Instance()->UseUniform1i("TreeTextured", "uTexture", 0);
	ShaderManager::Instance()->UseUniform4fv("TreeTextured", "uAmb", amb);
	ShaderManager::Instance()->UseUniform4fv("TreeTextured", "uDif", dif);
	ShaderManager::Instance()->UseUniform4fv("TreeTextured", "uSpec",spec);
	ShaderManager::Instance()->UseUniform1f("TreeTextured", "uShine", shine);
	ShaderManager::Instance()->UnuseProgram("TreeTextured");

	// Set all uniforms (can do this here due to shaders only used for trees)
	ShaderManager::Instance()->AddNewShader("TreeNonSmooth", 
		"Resources/Shaders/TreeNonSmooth.vert",
		"Resources/Shaders/TreeNonSmooth.frag");
	ShaderManager::Instance()->UseProgram("TreeNonSmooth");
	ShaderManager::Instance()->AddAttribTo("TreeNonSmooth", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("TreeNonSmooth", "aNormal", 3, 20);
	ShaderManager::Instance()->AddUniformTo("TreeNonSmooth", "uShine");
	ShaderManager::Instance()->AddUniformTo("TreeNonSmooth", "uDif");
	ShaderManager::Instance()->AddUniformTo("TreeNonSmooth", "uSpec");
	ShaderManager::Instance()->AddUniformTo("TreeNonSmooth", "uAmb");
	ShaderManager::Instance()->AddUniformTo("TreeNonSmooth", "uLightDir");
	ShaderManager::Instance()->UseUniform4fv("TreeNonSmooth", "uAmb", amb);
	ShaderManager::Instance()->UseUniform4fv("TreeNonSmooth", "uDif", dif);
	ShaderManager::Instance()->UseUniform4fv("TreeNonSmooth", "uSpec",spec);
	ShaderManager::Instance()->UseUniform1f("TreeNonSmooth", "uShine", shine);
	ShaderManager::Instance()->UnuseProgram("TreeNonSmooth");

	_iterations = atoi(configData["Iterations"].c_str());

	if (configData["StartMode"] == "Textured")
	{
		_curMode = Textured;
		_shaderName = "TreeTextured";
	}
	else if (configData["StartMode"] == "Wireframe")
	{
		_curMode = Wireframe;
		_shaderName = "TreeNone";
	}
	else if(configData["StartMode"] == "NonSmooth")
	{
		_curMode = NonSmooth;
		_shaderName = "TreeNonSmooth";
	}
	else if(configData["StartMode"] == "Smooth")
	{
		_curMode = Smooth;
		_shaderName = "TreeSmooth";
	}

	Fractal(0);

	if(!Utility::Instance()->ReturnConfigField(configData, "Seasons", configLines))
		return false;

	float timePerSeason = (float)atof(configData["TimeBetween"].c_str());

	_growRate = ((float)_iterations/timePerSeason);

	if ((configData["StartSeason"] == "Summer") || (configData["StartSeason"] == "Autumn"))
	{
		for (int i = 0; i < _branches.size(); ++i)
		{
			_branches[i]._scale = 1.0f;
		}
		_levelToGrow = _iterations -1;
	}

	return true;
}

const void Branches::Render()
{
	if (_curMode == Wireframe)
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}

	_vbo.BindBuffer();

	ShaderManager::Instance()->UseProgram(_shaderName);
	ShaderManager::Instance()->UseUniform3fv(_shaderName, "uLightDir", 
		Lights::Instance()->GetSunDirection());


	if(_curMode == Textured)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _texID);
	}


	for (int i = 0; i < _branches.size(); ++i)
	{
		if (_branches[i]._level > _levelToGrow)
		{
			continue;
		}
		glPushMatrix();
		glMultMatrixf(_branches[i]._matrix);
		glScalef(_branches[i]._scale, _branches[i]._scale, _branches[i]._scale);
		_vbo.Render(GL_TRIANGLES);
		glPopMatrix();
	}

	ShaderManager::Instance()->UnuseProgram(_shaderName);
	_vbo.UnbindBuffer();

	if (_curMode == Wireframe)
	{
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}

 	if(_curMode == Textured)
 	{
 		glBindTexture(GL_TEXTURE_2D, 0);
 	}

}

const void Branches::Grow( const float dt )
{
	bool updated = false;

	if (_levelToGrow == -1)
	{
		_levelToGrow = 0;
	}

	for (int i = 0; i < _branches.size(); ++i)
	{
		if (_branches[i]._level == _levelToGrow)
		{
			_branches[i]._scale += dt * _growRate;

			if (_branches[i]._scale >= 1.0f)
			{
				_branches[i]._scale = 1.0f;
				if (!updated)
				{
					++_levelToGrow;
					updated = true;
				}
			}
		}
	}
}

const void Branches::Shrink( const float dt )
{
	bool updated = false;

	if (_levelToGrow == _iterations)
	{
		_levelToGrow = _iterations-1;
	}

	for(int i = _branches.size()-1; i >= 0; i--)
	{
		if (_branches[i]._level == _levelToGrow)
		{
			_branches[i]._scale -= dt * (_growRate*2);

			if (_branches[i]._scale <= 0.0f)
			{
				_branches[i]._scale = 0.0f;
				if (!updated)
				{
					--_levelToGrow;
					updated = true;
				}
			}
		}
	}
}

const void Branches::UpdateRenderMode()
{
	switch (_curMode)
	{
	case Wireframe:
		_curMode = NonSmooth;
		_shaderName = "TreeNonSmooth";
		break;
	case NonSmooth:
		_curMode = Smooth;
		_shaderName = "TreeSmooth";
		break;
	case Smooth:
		_curMode = Textured;
		_shaderName = "TreeTextured";
		break;
	case Textured:
		_curMode = Wireframe;
		_shaderName = "TreeNone";
		break;
	}
}

const void Branches::Fractal( int level )
{
	long savedSeed;

	// Place matrix into branch matrices
	Branch b;
	glGetFloatv(GL_MODELVIEW_MATRIX, b._matrix);
	b._level = level;
	b._scale = 0.0f;

	_branches.push_back(b);

	glPushMatrix();
	glTranslatef(0,0.2f,0);
	glScalef(0.7f,0.7f,0.7f);

	if(level == _iterations-1)
	{
		// Place matrix into leaf matrices
		Leaf::LeafMats leafM;
		glGetFloatv(GL_MODELVIEW_MATRIX, leafM._curMat);
		glGetFloatv(GL_MODELVIEW_MATRIX, leafM._orgMat);
		_leaves.push_back(leafM);
	}
	if (level != _iterations-1)
	{
		savedSeed = ((float)rand()/(float)RAND_MAX) * ULONG_MAX;

		glPushMatrix();
		glRotatef(110 + ((float)rand()/(float)RAND_MAX)*40, 0,1,0);
		glRotatef(30 + ((float)rand()/(float)RAND_MAX)*20, 0,0,1);
		Fractal(level + 1);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-130 + ((float)rand()/(float)RAND_MAX)*40, 0,1,0);
		glRotatef(30 + ((float)rand()/(float)RAND_MAX)*20, 0,0,1);
		Fractal(level + 1);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-20 + ((float)rand()/(float)RAND_MAX)*40, 0,1,0);
		glRotatef(30 + ((float)rand()/(float)RAND_MAX)*20, 0,0,1);
		Fractal(level + 1);
		glPopMatrix();
	}
	glPopMatrix();
}
