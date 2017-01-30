#pragma once
#include "IShape.h"
using namespace gxbase;

class ITexturedShape :
	public IShape
{
private:
	GLuint _texID;

public:
	explicit ITexturedShape(const Vector3f& pos = Vector3f(0,0,0),
		const Vector3f& scale = Vector3f(0,0,0),
		const Vector3f& rotation = Vector3f(0,0,0))
		: IShape(pos,scale,rotation), _texID(0)
	{}
	virtual ~ITexturedShape(void){}

	virtual const void Render(const bool sun) = 0;

	const void InitializeTexture(const char* filepath)
	{
		Image texture;
		texture.Load(filepath);

		glGenTextures(1, &_texID);
		glBindTexture(GL_TEXTURE_2D, _texID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		texture.gluBuild2DMipmaps();
		texture.Free();
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	const void BindTexture()
	{
		glBindTexture(GL_TEXTURE_2D, _texID);
		glActiveTexture(GL_TEXTURE0);
	}

	const void UnbindTexture() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};