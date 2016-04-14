#ifndef _InfoFPS_H_
#define _InfoFPS_H_

#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>

class InfoFPS
{
public:
	InfoFPS();
	InfoFPS(const InfoFPS&);
	~InfoFPS();

	void Initialize();
	void Update();
	int* GetFPS();

private:
	int mFPS, mcount;
	unsigned long mstartTime;
};

#endif