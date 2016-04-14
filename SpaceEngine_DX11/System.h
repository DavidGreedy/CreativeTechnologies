#ifndef _SystemH_
#define _SystemH_

#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "Application.h"

class System
{
public:
	System();
	System(const System&);
	~System();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR mapplicationName;
	HINSTANCE mhinstance;
	HWND mhwnd;

	Application* mApplication;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

static System* ApplicationHandle = 0;

#endif
