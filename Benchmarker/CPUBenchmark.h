#pragma once
#include <Windows.h>

enum class LogType: INT8
{
	FULL,
	SHORT
};

class CPUBenchmark
{
private:
	LARGE_INTEGER Frequency;
	LARGE_INTEGER StartCounter;
	LARGE_INTEGER EndCounter;

	LogType CurrentLogType;
	const char *CurrentTestCase;

public:

	CPUBenchmark();
	void Start(const char *TestName);
	void Stop();
	void SetBenchmarkLogType(LogType NewLogType);
};
