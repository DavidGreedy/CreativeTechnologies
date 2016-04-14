#ifndef _APPLICATION_H_
#define _APPLICATION_H_

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = false;
const float SCREEN_DEPTH = 10000.0f; //Change render distance
const float SCREEN_NEAR = 0.1f;

#include "Input.h"
#include "Direct3D.h"
#include "Camera.h"
#include "Timer.h"
#include "CameraController.h"
#include "InfoFPS.h"
#include "InfoCPU.h"
#include "Light.h"
#include "Frustum.h"
#include "AntTweakBar.h"
#include "Planet.h"
#include "ShaderColor.h"
#include "GLOBALS.h"

#include <vector>

class Application
{
public:
	Application();
	Application(const Application&);
	~Application();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

private:
	bool HandleInput(float);
	bool RenderGraphics();

private:

	Input* mInput;
	Direct3D* mDirect3D;
	Camera* mCamera;
	Timer* mTimer;
	CameraController* mCameraController;
	InfoFPS* mFps;
	InfoCPU* mCpu;
	Frustum* mFrustum;
	Planet* mPlanet;
	ShaderColor* mShaderColor;
};
#endif