#include "InfoFPS.h"

InfoFPS::InfoFPS()
{

}

InfoFPS::InfoFPS(const InfoFPS& other)
{

}

InfoFPS::~InfoFPS()
{

}

void InfoFPS::Initialize()
{
	mFPS = 0;
	mcount = 0;
	mstartTime = timeGetTime();
	return;
}

void InfoFPS::Update()
{
	mcount++;

	if (timeGetTime() >= (mstartTime + 1000))
	{
		mFPS = mcount;
		mcount = 0;

		mstartTime = timeGetTime();
	}
}

int* InfoFPS::GetFPS()
{
	return &mFPS;
}