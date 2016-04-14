#ifndef _Input_H_
#define _Input_H_

#define DIRECTINPUT_VERSION 0x0800

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <dinput.h>

class Input
{
public:
	Input();
	Input(const Input&);
	~Input();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Update();

	void GetMouseLocation(int&, int&);

	bool IsEscapePressed();

	int CheckMouseWheel();

	unsigned char mKeyboardState[256];
	DIMOUSESTATE mMouseState;
private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:
	IDirectInput8* mDirectInput;
	IDirectInputDevice8* mKeyboard;
	IDirectInputDevice8* mMouse;


	int mScreenWidth, mScreenHeight;
	int mMouseX, mMouseY;

	long mPreviousScrollValue;
};

#endif