#ifndef _InfoCPU_H_
#define _InfoCPU_H_

#pragma comment(lib, "pdh.lib")

#include <pdh.h>

class InfoCPU
{
public:
	InfoCPU();
	InfoCPU(const InfoCPU&);
	~InfoCPU();

	void Initialize();
	void Shutdown();
	void Update();
	int GetCpuPercentage();

private:
	bool mcanReadCpu;
	HQUERY mqueryHandle;
	HCOUNTER mcounterHandle;
	unsigned long mlastSampleTime;
	long mcpuUsage;
};

#endif