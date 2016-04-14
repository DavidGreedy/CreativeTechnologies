#ifndef _TIMER_H_
#define _TIMER_H_

#include <windows.h>

class Timer
{
public:
	Timer();
	Timer(const Timer&);
	~Timer();

	bool Initialize();
	void Update();

	float GetTime();
	float GetDeltaTime();

private:
	INT64 mfrequency;
	float mticksPerMs;
	INT64 mstartTime;
	float mframeTime;
	float mdeltaTime;

};

#endif