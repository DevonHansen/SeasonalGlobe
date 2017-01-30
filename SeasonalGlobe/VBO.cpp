#include "VBO.h"
using namespace std;

VBO::VBO(void)
	: _vboID(0),_faceSize(0)
{
}


VBO::~VBO(void)
{
}

const void VBO::CreateVBO( const vector<Utility::Vertex>& faces )
{
	glex::Load();
	_faceSize = faces.size();

	glGenBuffers(1, &_vboID);
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Utility::Vertex)*_faceSize, 
		&(faces[0]), GL_STATIC_DRAW);

	glTexCoordPointer(2, GL_FLOAT, sizeof(Utility::Vertex), Utility::Instance()->BufferOffset(12));
	glNormalPointer(GL_FLOAT, sizeof(Utility::Vertex), Utility::Instance()->BufferOffset(20));
	glColorPointer(4, GL_FLOAT, sizeof(Utility::Vertex), Utility::Instance()->BufferOffset(32));
	glVertexPointer(3, GL_FLOAT, sizeof(Utility::Vertex), Utility::Instance()->BufferOffset(0));

	glBindBuffer(GL_ARRAY_BUFFER,0);
}

const void VBO::BindBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER,_vboID);
}

const void VBO::Render(GLenum type) const
{
	glDrawArrays(type, 0, _faceSize);
}

const void VBO::UnbindBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER,0);
}
