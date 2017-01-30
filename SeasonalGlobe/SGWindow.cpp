#include "SGWindow.h"
#include <sstream>
#include <string>
#ifdef _DEBUG
#include <iostream>
using namespace std;
#endif // _DEBUG

SGWindow::SGWindow(void)
	: _speed(1.0f)
{
	SetDepthBits(24);
	SetStencilBits(16);
}


SGWindow::~SGWindow(void)
{
}

void SGWindow::OnCreate()
{
	GLWindowEx::OnCreate();
	vector<string> configFileLines;
	Utility::Instance()->LoadConfigFile("Resources/Config/Config.txt", configFileLines);
	map<string,string> configData;
	Utility::Instance()->ReturnConfigField(configData, "MyWindow", configFileLines);

	SetSize(atoi(configData["WindowSizeX"].c_str()), atoi(configData["WindowSizeY"].c_str()));
	SetDepthBits(atoi(configData["DepthBits"].c_str()));
	SetTitle(configData["Title"].c_str());

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f,
		(GLfloat)atoi(configData["WindowSizeX"].c_str())/ (GLfloat)atoi(configData["WindowSizeY"].c_str()),
		0.1f,10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glViewport(0,0, Width(), Height());
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	configData.clear();

	Utility::Instance()->ReturnConfigField(configData, "Camera", configFileLines);

	stringstream ss;
	ss << configData["Position"];
	ss >> _camPos;

	ss << configData["Rotation"];
	ss >> _camRotation;

	ss.clear();
	configData.clear();

	GLWindowEx::OnCreate();
	glex::Load();

	_seasonalGlobe.CreateWorld();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_CCW);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
#ifdef _DEBUG
	cout << "MyWindow::OnCreate Called" << endl;
#endif
}

void SGWindow::OnDestroy()
{
	GLWindowEx::OnDestroy();
}

void SGWindow::OnDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(_camPos[0],_camPos[1],_camPos[2]);
	glRotatef(_camRotation[0], 1,0,0);
	glRotatef(_camRotation[1], 0,1,0);
	glRotatef(_camRotation[2], 0,0,1);

	bool inside = false;
	if (_camPos[2] < 1 && _camPos[2] > -1)
		inside = true;

	_seasonalGlobe.Render(inside, _camPos);

	glPopMatrix();

	SwapBuffers();
}

void SGWindow::OnResize( int w, int h )
{
	gluPerspective(45.0f,
		(GLfloat)w/(GLfloat)h,
		0.1f,10000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glViewport(0,0, Width(), Height());
}

void SGWindow::OnKeyboard( int key, bool down )
{
	if(!down)
		return;

	switch(key)
	{
	case 38:
		_camRotation[0] += 1.0f;
		break;
	case 40:
		_camRotation[0] -= 1.0f;
		break;
	case 37:
		_camRotation[1] -= 1.0f;
		break;
	case 39:
		_camRotation[1] += 1.0f;
		break;
	case 83:
		_camPos[2] -= 0.1f;
		break;
	case 87:
		_camPos[2] += 0.1f;
		break;
	case 65:
		_camPos[0] -= 0.1f;
		break;
	case 68:
		_camPos[0] += 0.1f;
		break;
	case 77:						//' m' (drawing mode for tree)
		_seasonalGlobe.UpdateRenderMode();
		break;
	case 187:
		if (!GLWindowEx::GetShiftKey())
			break;
	case 107:		// '+' (speed up seasons)
		_speed += 0.1f;
		break;
	case 109:		//'-' (slow down seasons)
	case 189:
		_speed -= 0.1f;
		break;
		// case 83:		's' (toggle lights/sun)
	}
}

void SGWindow::OnIdle()
{
	_seasonalGlobe.Update(_speed * App::GetDeltaTime());
	Redraw();
}
