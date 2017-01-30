//////////////////////////////////////////////
// SGApp
//--------------------------------------------
// Created By: Devon Hansen
//--------------------------------------------
// Parasoft warnings:
//		- MyApp does not define any constructors.
//		- Data Members declared as public
//			- Not done due to GXBase usage
//--------------------------------------------
// Description: GXBase needs this to load the program

#include "GXBase/include/GXBase.h"
#include "SGWindow.h"
using namespace gxbase;

class SGApp : public App{
public:
	SGWindow globe;
};

static SGApp seasonalGlobe;