#include "Utility.h"
#include <iterator>
#include <fstream>
#include <ctime>
#include <sstream>
using namespace std;

Utility* Utility::_instance = NULL;

Utility::Utility(void)
{
}

Utility::~Utility(void)
{
}

const bool Utility::LoadConfigFile( const char* filepath, vector<string>& result )
{
	result.clear();

	ifstream in(filepath);

	if(!in)
	{
#ifdef _DEBUG
		cout << "Unable to open file " << filepath << endl;
#endif // _DEBUG
		return false;
	}
	else
	{
		copy(istream_iterator<string>(in), istream_iterator<string>(),
			inserter(result, result.begin()));

		in.close();

		return true;
	}
}

const bool Utility::ReturnConfigField( map<string, string>& result, const string& dataRegion, 
	vector<string>& configFile ) const
{
	result.clear();
	for(vector<string>::iterator iter = configFile.begin();
		iter!=configFile.end();
		iter++)
	{
		if (*iter == dataRegion)
		{
			++iter;		// Found name of dataRegion, skip this word
			if (*iter == "{")
				++iter;		// Found open brace, skip this	

			while (*iter != "}")
			{
				string name, data;
				name = *iter;

				++iter;

				data = *iter;

				result[name] = data;

				++iter;
			}
			return true;
		}
	}

	return false;
}

const float Utility::RandomFloat( const float min, const float max ) const
{
	return ((max-min)*((float)rand()/RAND_MAX)) + min;
}

const void* Utility::BufferOffset( const int x ) const
{
	return ((char*)NULL + x);
}

const void Utility::StringToVector(const string& s, Vector2f& v )
{
	stringstream ss;

	ss << s;
	ss >> v;
}

const void Utility::StringToVector(const string& s, Vector3f& v )
{
	stringstream ss;

	ss << s;
	ss >> v;
}

const void Utility::StringToVector(const string& s, Vector4f& v )
{
	stringstream ss;

	ss << s;
	ss >> v;
}