//////////////////////////////////////////////
// SGWindow
//--------------------------------------------
// Created By: Devon Hansen
//--------------------------------------------
// Parasoft warnings:
//--------------------------------------------
// Description: Holds all methods used by GXBase

#pragma once
#include "World.h"
#include "Maths/Vector3f.h"
#include "GXBase/include/GXBase.h"
using namespace gxbase;

class SGWindow : public GLWindowEx
{
private:
	Vector3f _camPos;
	Vector3f _camRotation;
	World _seasonalGlobe;
	float _speed;

public:
	explicit SGWindow(void);
	~SGWindow(void);

	void OnCreate();
	void OnDestroy();
	void OnDisplay();
	void OnResize(int w, int h);
	void OnKeyboard(int key, bool down);
	void OnIdle();
};