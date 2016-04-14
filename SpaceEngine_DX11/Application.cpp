#include "Application.h"

using namespace std;

Light* Globals::mLight;
XMFLOAT4X4 Globals::mWorldMatrix;
XMFLOAT4X4 Globals::mViewMatrix;
XMFLOAT4X4 Globals::mProjectionMatrix;

Application::Application()
{
	mInput = 0;
	mDirect3D = 0;
	mCamera = 0;
	mTimer = 0;
	mCameraController = 0;
	mFps = 0;
	mCpu = 0;
	mFrustum = 0;
	mPlanet = 0;
	mShaderColor = 0;
}

Application::Application(const Application& other)
{

}

Application::~Application()
{

}

bool Application::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;
	XMFLOAT4X4 baseViewMatrix;
	char videoCard[128];
	int videoMemory;

#pragma region Initialisation
	mInput = new Input();
	result = mInput->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	mDirect3D = new Direct3D;
	result = mDirect3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX 11.", L"Error", MB_OK);
		return false;
	}

	mCamera = new Camera;
	mCamera->SetPosition(XMFLOAT3(0, 0, -2000));
	mCamera->Render();
	mCamera->GetViewMatrix(baseViewMatrix);

	mFrustum = new Frustum;
	mTimer = new Timer;

	// Initialize the timer object.
	result = mTimer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	mCameraController = new CameraController;
	mCameraController->SetPosition(XMFLOAT3(0, 0, -2000));

	mFps = new InfoFPS;
	mFps->Initialize();

	mCpu = new InfoCPU;
	mCpu->Initialize();

	mDirect3D->GetVideoCardInfo(videoCard, videoMemory);

	Globals::mLight = new Light();
	Globals::mLight->SetAmbientColor(0.05f, 0.05f, 0.05f, 1.0f);
	Globals::mLight->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	Globals::mLight->SetDirection(1.0f, 1.0f, 0.0f);

	mPlanet = new Planet(mDirect3D->GetDevice(), XMFLOAT3(100, 100, 100), XMFLOAT3(1, 0, 0), XMFLOAT3(0, 0, 0));
	mPlanet->Initialise(mDirect3D->GetDevice(), hwnd);

	if (!TwInit(TW_DIRECT3D11, mDirect3D->GetDevice()))
	{
		MessageBoxA(hwnd, TwGetLastError(), "AntTweakBar initialization failed", MB_OK | MB_ICONERROR);
		return 0;
	}

	TwBar *bar = TwNewBar("Terrain Parameters");
	//TwDefine(" GLOBAL help='Help Menu' "); // Message added to the help bar.
	int barSize[2] = { 300, 200 };
	int barPos[2] = { 1280 - barSize[1] - 110, 10 };
	TwAddVarRW(bar, "Wireframe", TW_TYPE_BOOL32, mDirect3D->GetWireframeValue(), "group=RENDERING");
	TwAddVarRW(bar, "Backface Culling", TW_TYPE_BOOL32, mDirect3D->GetCullMode(), "group=RENDERING");
	TwAddVarRW(bar, "Draw Count", TW_TYPE_INT32, mPlanet->GetDrawCount(), "group=RENDERING");
	//TwAddVarRW(bar, "Show Quadtree", TW_TYPE_BOOL32, mPlanet->GetDebug(), "group=RENDERING");
	TwAddVarRW(bar, "Camera Speed", TW_TYPE_FLOAT, mCameraController->GetMoveSpeed(), "group=RENDERING");


	TwAddVarRW(bar, "FPS", TW_TYPE_INT32, mFps->GetFPS(), "group=PERFORMANCE");

	mDirect3D->SetRenderState();

#pragma endregion

	return true;
}

void Application::Shutdown()
{
	if (mFrustum)
	{
		delete mFrustum;
		mFrustum = 0;
	}

	if (mCpu)
	{
		mCpu->Shutdown();
		delete mCpu;
		mCpu = 0;
	}

	if (mFps)
	{
		delete mFps;
		mFps = 0;
	}

	if (mCameraController)
	{
		delete mCameraController;
		mCameraController = 0;
	}

	if (mTimer)
	{
		delete mTimer;
		mTimer = 0;
	}

	if (mCamera)
	{
		delete mCamera;
		mCamera = 0;
	}

	if (mDirect3D)
	{
		mDirect3D->Shutdown();
		delete mDirect3D;
		mDirect3D = 0;
	}

	if (mInput)
	{
		mInput->Shutdown();
		delete mInput;
		mInput = 0;
	}

	return;
}

bool Application::Frame()
{
	if (!mInput->Update())
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (mInput->IsEscapePressed())
	{
		return false;
	}

	// Update the system stats.
	mTimer->Update();
	mFps->Update();
	mCpu->Update();

	// Do the frame input processing.
	if (!HandleInput(mTimer->GetTime()))
	{
		return false;
	}

	mDirect3D->SetRenderState();

	if (!RenderGraphics())
	{
		return false;
	}

	return true;
}

bool Application::HandleInput(float frameTime)
{
	XMFLOAT3 position, rotation;

	mCameraController->SetFrameTime(frameTime);


	if (mInput->mKeyboardState[DIK_A] & 0x80)
	{
		mCameraController->MoveLeft();
	}

	if (mInput->mKeyboardState[DIK_D] & 0x80)
	{
		mCameraController->MoveRight();
	}

	if (mInput->mKeyboardState[DIK_W] & 0x80)
	{
		mCameraController->MoveForward();
	}

	if (mInput->mKeyboardState[DIK_S] & 0x80)
	{
		mCameraController->MoveBackward();
	}

	if (mInput->mKeyboardState[DIK_E] & 0x80)
	{
		mCameraController->MoveUpward();
	}

	if (mInput->mKeyboardState[DIK_Q] & 0x80)
	{
		mCameraController->MoveDownward();
	}

	if (mInput->mKeyboardState[DIK_UPARROW] & 0x80)
	{
		mCameraController->LookUpward();
	}

	if (mInput->mKeyboardState[DIK_DOWNARROW] & 0x80)
	{
		mCameraController->LookDownward();
	}

	if (mInput->mKeyboardState[DIK_LEFTARROW] & 0x80)
	{
		mCameraController->LookLeft();
	}

	if (mInput->mKeyboardState[DIK_RIGHTARROW] & 0x80)
	{
		mCameraController->LookRight();
	}

	if (mInput->CheckMouseWheel() == 1)
	{
		mCameraController->DecreaseMoveSpeed();
	}
	else if (mInput->CheckMouseWheel() == 2)
	{
		mCameraController->IncreaseMoveSpeed();
	}

	// Get the view point position/rotation.
	mCameraController->GetPosition(position);
	mCameraController->GetRotation(rotation);

	// Set the position of the camera.
	mCamera->SetPosition(position);
	mCamera->SetRotation(rotation);

	return true;
}

bool Application::RenderGraphics()
{
	XMFLOAT4X4 worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

	// Clear the scene.
	mDirect3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	mCamera->Render();

	// Get the world, view, projection, and ortho matrices from the camera and Direct3D objects.
	mDirect3D->GetWorldMatrix(Globals::mWorldMatrix);
	mCamera->GetViewMatrix(Globals::mViewMatrix);
	mDirect3D->GetProjectionMatrix(Globals::mProjectionMatrix);
	mDirect3D->GetOrthoMatrix(orthoMatrix);

	mFrustum->ConstructFrustum(SCREEN_DEPTH);

	mPlanet->Render(mDirect3D->GetDeviceContext(), mDirect3D->GetDevice(), mFrustum, mCamera);

	TwDraw();

	// Present the rendered scene to the screen.
	mDirect3D->EndScene();

	return true;
}
