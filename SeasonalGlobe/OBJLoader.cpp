#include "OBJLoader.h"
#include <fstream>
#include <sstream>
using namespace std;

OBJLoader::OBJLoader(void)
{
#ifdef _DEBUG
	_debugLineFlag = false;
#endif
}

OBJLoader::~OBJLoader(void)
{
}

const bool OBJLoader::LoadFile( const char* filepath )
{
	ifstream in(filepath);

	if(!in)
	{
#ifdef _DEBUG
		cout << "Unable to load file " << filepath << endl;
#endif // _DEBUG

		in.close();

		return false;
	}
	else
	{
		string tempLine;

		while(in.good())
		{
			getline(in, tempLine);
			_fileLines.push_back(tempLine);
		}

		in.close();

		return true;
	}
}

const bool OBJLoader::LoadFaces( const char* filepath, std::vector<Utility::Vertex>& result )
{
#ifdef _DEBUG
	_debugLineFlag = false;
#endif // _DEBUG

	_vertices.clear();
	_normals.clear();
	_textureCoords.clear();
	_fileLines.clear();
	result.clear();

	if (!LoadFile(filepath))
		return false;

	for (vector<string>::iterator i = _fileLines.begin();
		i != _fileLines.end();
		i++)
	{
		string first;
		stringstream ss(*i);

		ss >> first;

		if (first == "v")
		{
			Vector3f temp;
			float x,y,z;

			ss >> x >> y >> z;

			temp[0] = x;
			temp[1] = y;
			temp[2] = z;

			_vertices.push_back(temp);

		} 
		else if (first == "vn")
		{
			Vector3f temp;
			float x,y,z;

			ss >> x >> y >> z;

			temp[0] = x;
			temp[1] = y;
			temp[2] = z;

			_normals.push_back(temp);
		}
		else if (first == "vt")
		{
			Vector2f temp;
			float x,y;

			ss >> x >> y;

			temp[0] = x;
			temp[1] = y;

			_textureCoords.push_back(temp);
		}
		else if (first == "f")
		{
			// Need to do this 3 times (three vertex's coming through!!)
			string s;

			ss >> s;

			int backSlashes = 0;
			bool doubleBS = false;

			for (unsigned int i = 0; i < s.length(); ++i)
			{

				if(s[i] == '/')
				{
					if(s[i+1] == '/')
					{
						doubleBS = true;
					}

					++backSlashes;
				}
			}

			if (doubleBS && backSlashes == 2)	// vector//normal
			{
				int x,y;
				char c;

				// This is done each time due to getting first "word"
				// out of the stream already
				stringstream tempSS(s);
				tempSS >> x >> c >> c >> y;

				Utility::Vertex v;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];

				v._norm[0] = _normals[y-1][0];
				v._norm[1] = _normals[y-1][1];
				v._norm[2] = _normals[y-1][2];

				result.push_back(v);

				ss >> x >> c >> c >> y;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];

				v._norm[0] = _normals[y-1][0];
				v._norm[1] = _normals[y-1][1];
				v._norm[2] = _normals[y-1][2];
				result.push_back(v);

				ss >> x >> c >> c >> y;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];

				v._norm[0] = _normals[y-1][0];
				v._norm[1] = _normals[y-1][1];
				v._norm[2] = _normals[y-1][2];
				result.push_back(v);

#ifdef _DEBUG
				if (!_debugLineFlag)
				{
					cout << "Face Format: v1//vn1" << endl;
					_debugLineFlag = true;
				}
#endif
			}
			else if(!doubleBS && backSlashes == 2)	// vector/texture/normal
			{
				int x,y,z;
				char c;

				stringstream tempSS(s);
				tempSS >> x >> c >> y >> c >> z;

				Utility::Vertex v;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];

				v._tex[0] = _textureCoords[y-1][0];
				v._tex[1] = _textureCoords[y-1][1];

				v._norm[0] = _normals[z-1][0];
				v._norm[1] = _normals[z-1][1];
				v._norm[2] = _normals[z-1][2];

				result.push_back(v);

				ss >> x >> c >> y >> c >> z;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];

				v._tex[0] = _textureCoords[y-1][0];
				v._tex[1] = _textureCoords[y-1][1];

				v._norm[0] = _normals[z-1][0];
				v._norm[1] = _normals[z-1][1];
				v._norm[2] = _normals[z-1][2];

				result.push_back(v);

				ss >> x >> c >> y >> c >> z;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];

				v._tex[0] = _textureCoords[y-1][0];
				v._tex[1] = _textureCoords[y-1][1];

				v._norm[0] = _normals[z-1][0];
				v._norm[1] = _normals[z-1][1];
				v._norm[2] = _normals[z-1][2];

				result.push_back(v);

#ifdef _DEBUG
				if (!_debugLineFlag)
				{
					cout << "Face Format: v1/vt1/vn1" << endl;
					_debugLineFlag = true;
				}
#endif
			}
			else if(!doubleBS && backSlashes == 1)	// vector/texture
			{
				int x,y;
				char c;

				stringstream tempSS(s);
				tempSS >> x >> c >> y;

				Utility::Vertex v;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];

				v._tex[0] = _textureCoords[y-1][0];
				v._tex[1] = _textureCoords[y-1][1];
				result.push_back(v);

				ss >> x >> c >> y;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];

				v._tex[0] = _textureCoords[y-1][0];
				v._tex[1] = _textureCoords[y-1][1];
				result.push_back(v);

#ifdef _DEBUG
				if (!_debugLineFlag)
				{
					cout << "Face Format: v1/vt1" << endl;
					_debugLineFlag = true;
				}
#endif
			}
			else if(!doubleBS && backSlashes == 0)	// vector
			{
				int x;

				stringstream tempSS(s);
				tempSS >> x;

				Utility::Vertex v;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];
				result.push_back(v);

				ss >> x;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];
				result.push_back(v);

				ss >> x;
				v._pos[0] = _vertices[x-1][0];
				v._pos[1] = _vertices[x-1][1];
				v._pos[2] = _vertices[x-1][2];
				result.push_back(v);

#ifdef _DEBUG
				if (!_debugLineFlag)
				{
					cout << "Face Format: v1" << endl;
					_debugLineFlag = true;
				}
#endif
			}
			else
			{
#ifdef _DEBUG
				if (!_debugLineFlag)
				{
					cout << "Face Format incorrect!" << endl;
					_debugLineFlag = true;
				}
#endif
				return false;
			}
		}
	}

	_fileLines.clear();
	_vertices.clear();
	_normals.clear();
	_textureCoords.clear();

	return true;
}
