#include "InfoCPU.h"

InfoCPU::InfoCPU()
{

}

InfoCPU::InfoCPU(const InfoCPU& other)
{

}

InfoCPU::~InfoCPU()
{

}

void InfoCPU::Initialize()
{
	PDH_STATUS status;


	// Initialize the flag indicating whether this object can read the system cpu usage or not.
	mcanReadCpu = true;

	// Create a query object to poll cpu usage.
	status = PdhOpenQuery(NULL, 0, &mqueryHandle);
	if (status != ERROR_SUCCESS)
	{
		mcanReadCpu = false;
	}

	// Set query object to poll all cpus in the system.
	status = PdhAddCounter(mqueryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &mcounterHandle);
	if (status != ERROR_SUCCESS)
	{
		mcanReadCpu = false;
	}

	mlastSampleTime = GetTickCount();

	mcpuUsage = 0;

	return;
}

void InfoCPU::Shutdown()
{
	if (mcanReadCpu)
	{
		PdhCloseQuery(mqueryHandle);
	}

	return;
}

void InfoCPU::Update()
{
	PDH_FMT_COUNTERVALUE value;

	if (mcanReadCpu)
	{
		if ((mlastSampleTime + 1000) < GetTickCount())
		{
			mlastSampleTime = GetTickCount();

			PdhCollectQueryData(mqueryHandle);

			PdhGetFormattedCounterValue(mcounterHandle, PDH_FMT_LONG, NULL, &value);

			mcpuUsage = value.longValue;
		}
	}

	return;
}

int InfoCPU::GetCpuPercentage()
{
	int usage;

	if (mcanReadCpu)
	{
		usage = (int)mcpuUsage;
	}
	else
	{
		usage = 0;
	}

	return usage;
}