#include "Input.h"

Input::Input()
{
	mDirectInput = 0;
	mKeyboard = 0;
	mMouse = 0;
}

Input::Input(const Input& other)
{

}

Input::~Input()
{

}

bool Input::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;


	// Store the screen size which will be used for positioning the mouse cursor.
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	// Initialize the location of the mouse on the screen.
	mMouseX = 0;
	mMouseY = 0;

	// Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&mDirectInput, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the keyboard.
	result = mDirectInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = mKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the keyboard to not share with other programs.
	result = mKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Now acquire the keyboard.
	result = mKeyboard->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	// Initialize the direct input interface for the mouse.
	result = mDirectInput->CreateDevice(GUID_SysMouse, &mMouse, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = mMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(result))
	{
		return false;
	}

	// Set the cooperative level of the mouse to share with other programs.
	result = mMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
	{
		return false;
	}

	// Acquire the mouse.
	result = mMouse->Acquire();
	if (FAILED(result))
	{
		return false;
	}

	//mPreviousScrollValue = mMouseState.lZ;

	return true;
}

void Input::Shutdown()
{
	if (mMouse)
	{
		mMouse->Unacquire();
		mMouse->Release();
		mMouse = 0;
	}
	if (mKeyboard)
	{
		mKeyboard->Unacquire();
		mKeyboard->Release();
		mKeyboard = 0;
	}

	if (mDirectInput)
	{
		mDirectInput->Release();
		mDirectInput = 0;
	}

	return;
}

bool Input::Update()
{
	bool result;

	result = ReadKeyboard();
	if (!result)
	{
		return false;
	}

	result = ReadMouse();
	if (!result)
	{
		return false;
	}

	ProcessInput();

	return true;
}

bool Input::ReadKeyboard()
{
	HRESULT result;


	// Read the keyboard device.
	result = mKeyboard->GetDeviceState(sizeof(mKeyboardState), (LPVOID)&mKeyboardState);
	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mKeyboard->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

bool Input::ReadMouse()
{
	HRESULT result;


	// Read the mouse device.
	result = mMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mMouseState);
	if (FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			mMouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}

void Input::ProcessInput()
{
	// Update the location of the mouse cursor based on the change of the mouse location during the frame.
	mMouseX += mMouseState.lX;
	mMouseY += mMouseState.lY;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if (mMouseX < 0) { mMouseX = 0; }
	if (mMouseY < 0) { mMouseY = 0; }

	if (mMouseX > mScreenWidth) { mMouseX = mScreenWidth; }
	if (mMouseY > mScreenHeight) { mMouseY = mScreenHeight; }

	return;
}

void Input::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = mMouseX;
	mouseY = mMouseY;
	return;
}

bool Input::IsEscapePressed()
{
	// Do a bitwise and on the keyboard state to check if the escape key is currently being pressed.
	if (mKeyboardState[DIK_ESCAPE] & 0x80)
	{
		return true;
	}

	return false;
}

int Input::CheckMouseWheel()
{
	if (mMouseState.lZ < 0)
	{
		return 1;
	}
	else if (mMouseState.lZ > 0)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}
