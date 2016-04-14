#include "Timer.h"

Timer::Timer()
{

}

Timer::Timer(const Timer& other)
{

}

Timer::~Timer()
{

}

bool Timer::Initialize()
{
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&mfrequency);
	if (mfrequency == 0)
	{
		return false;
	}

	// Find out how many times the frequency counter ticks every millisecond.
	mticksPerMs = (float)(mfrequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&mstartTime);

	return true;
}

void Timer::Update()
{
	INT64 currentTime;
	float timeDifference;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - mstartTime);

	mframeTime = timeDifference / mticksPerMs;

	mdeltaTime = timeDifference / 10000;

	mstartTime = currentTime;

	return;
}

float Timer::GetTime()
{
	return mframeTime;
}

float Timer::GetDeltaTime()
{
	return mdeltaTime;
}