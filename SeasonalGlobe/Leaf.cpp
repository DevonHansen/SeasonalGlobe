#include "Leaf.h"
#include "ShaderManager.h"

Leaf::~Leaf(void)
{
}

const void Leaf::Initialize(const vector<LeafMats>& mats, bool allShown, const float timePerSeason )
{
	BuildVBO();

	Image texture;
	texture.Load("Resources/Textures/leaf.tga");
	glGenTextures(1, &_texID);
	glBindTexture(GL_TEXTURE_2D, _texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	texture.gluBuild2DMipmaps();
	texture.Free();
	glBindTexture(GL_TEXTURE_2D, 0);

	ShaderManager::Instance()->AddNewShader("Leaf", 
		"Resources/Shaders/Leaf.vert",
		"Resources/Shaders/Leaf.frag");
	ShaderManager::Instance()->UseProgram("Leaf");
	ShaderManager::Instance()->AddAttribTo("Leaf", "aVertex", 3, 0);
	ShaderManager::Instance()->AddAttribTo("Leaf", "aTexCoord", 2, 12);
	ShaderManager::Instance()->AddUniformTo("Leaf", "texSampler");
	ShaderManager::Instance()->UseUniform1i("Leaf", "texSampler", 0);
	ShaderManager::Instance()->AddUniformTo("Leaf", "uTimeInSeason");
	ShaderManager::Instance()->UseUniform1f("Leaf", "uTimeInSeason", timePerSeason/4);
	ShaderManager::Instance()->AddUniformTo("Leaf", "uTime");
	ShaderManager::Instance()->UnuseProgram("Leaf");

	_mats = mats;

	if(allShown)
		_amountShown = _mats.size()-1;

	_releaseTime = timePerSeason/((float)_mats.size());
}

const void Leaf::Render()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texID);	
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	_vbo.BindBuffer();
	ShaderManager::Instance()->UseProgram("Leaf");
	ShaderManager::Instance()->UseUniform1f("Leaf", "uTime", _totalTime*2);
	for (int i = 0; i < _amountShown; ++i)
	{
		glPushMatrix();
		glMultMatrixf(_mats[i]._curMat);
		_vbo.Render(GL_TRIANGLES);
		glPopMatrix();
	}
	ShaderManager::Instance()->UnuseProgram("Leaf");
	_vbo.UnbindBuffer();
	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, 0);
}

const void Leaf::Grow( const float dt )
{
	_curTime += dt;
	if (_curTime >= _releaseTime)
	{
		int amountRelease = _curTime*2/_releaseTime;
		_curTime = 0;
		_amountShown += amountRelease;

		if(_amountShown > _mats.size())
			_amountShown = _mats.size();
	}
}

const void Leaf::Die( const float dt, const float percSeason )
{
	_totalTime += dt;

	if (percSeason <= 75.0f)
	{
		_curTime += dt;
		if (_curTime >= _releaseTime)
		{
			_amountFalling += (_curTime*2/_releaseTime)*4;
			_curTime = 0;

			if (_amountFalling > _mats.size())
			{
				_amountFalling = _mats.size();
			}

			for (int i = 0; i < _amountFalling; ++i)
			{
				_mats[i]._curMat[13] -= dt*0.981f;

				if (_mats[i]._curMat[13] < 0.0f)
				{
					for (int j = 0; j < 16; ++j)
					{
						_mats[i]._curMat[j] = 0.0f;
					}
				}
			}
		}
	}
}

const void Leaf::BuildVBO()
{
	vector<Utility::Vertex> faces;

	Utility::Vertex t;
	// Bottom left
	t._pos = Vector3f(-0.3f, 0, 0);
	t._col = Vector4f(0,1,0,1);
	// Tex = default constructor
	faces.push_back(t);

	// Bottom Right
	t._pos = Vector3f(0.3f, 0, 0);
	t._tex = Vector2f(0,1);
	t._col = Vector4f(0,1,0,1);
	faces.push_back(t);

	// Top Left
	t._pos = Vector3f(-0.3f, 0.6f, 0);
	t._tex = Vector2f(1,0);
	t._col = Vector4f(0,1,0,1);
	faces.push_back(t);

	// Bottom Right
	t = faces[1];
	faces.push_back(t);

	// Top Right
	t._pos = Vector3f(0.3f, 0.6f, 0);
	t._tex = Vector2f(1,1);
	t._col = Vector4f(0,1,0,1);
	faces.push_back(t);

	// Top Left
	t = faces[2];
	faces.push_back(t);

	_vbo.CreateVBO(faces);
}

const void Leaf::Reset()
{
	_curTime = 0;
	_amountShown = 0;
	_totalTime = 0;
	_amountFalling = 0;

	for (int i = 0; i < _mats.size(); ++i)
	{
		for(int j = 0; j < 16; ++j)
		{
			_mats[i]._curMat[j] = _mats[i]._orgMat[j];
		}
	}
}
