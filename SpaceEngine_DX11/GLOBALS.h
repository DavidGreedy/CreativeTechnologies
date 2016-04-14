#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "Utility.h"
#include "Light.h"

class Globals
{
public:
	static XMFLOAT4X4 mWorldMatrix;
	static XMFLOAT4X4 mViewMatrix;
	static XMFLOAT4X4 mProjectionMatrix;

	static Light* mLight;

};

#endif