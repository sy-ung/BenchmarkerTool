#include "CPUBenchmark.h"
#include <iostream>

#define FOREGROUND_WHITE			(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_YELLOW       	(FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_CYAN		        (FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_MAGENTA	        (FOREGROUND_RED | FOREGROUND_BLUE)
#define FOREGROUND_BLACK		0

#define FOREGROUND_INTENSE_RED		(FOREGROUND_RED | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_GREEN	(FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_BLUE		(FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_WHITE	(FOREGROUND_WHITE | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_YELLOW	(FOREGROUND_YELLOW | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_CYAN		(FOREGROUND_CYAN | FOREGROUND_INTENSITY)
#define FOREGROUND_INTENSE_MAGENTA	(FOREGROUND_MAGENTA | FOREGROUND_INTENSITY)

#define BACKGROUND_WHITE			(BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN)
#define BACKGROUND_YELLOW	        (BACKGROUND_RED | BACKGROUND_GREEN)
#define BACKGROUND_CYAN		        (BACKGROUND_BLUE | BACKGROUND_GREEN)
#define BACKGROUND_MAGENTA	        (BACKGROUND_RED | BACKGROUND_BLUE)
#define BACKGROUND_BLACK		0

#define BACKGROUND_INTENSE_RED		(BACKGROUND_RED | BACKGROUND_INTENSITY)
#define BACKGROUND_INTENSE_GREEN	(BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define BACKGROUND_INTENSE_BLUE		(BACKGROUND_BLUE | BACKGROUND_INTENSITY)
#define BACKGROUND_INTENSE_WHITE	(BACKGROUND_WHITE | BACKGROUND_INTENSITY)
#define BACKGROUND_INTENSE_YELLOW	(BACKGROUND_YELLOW | BACKGROUND_INTENSITY)
#define BACKGROUND_INTENSE_CYAN		(BACKGROUND_CYAN | BACKGROUND_INTENSITY)
#define BACKGROUND_INTENSE_MAGENTA	(BACKGROUND_MAGENTA | BACKGROUND_INTENSITY)

CPUBenchmark::CPUBenchmark()
{
	CurrentLogType = LogType::FULL;
}

void CPUBenchmark::Start(const char *TestName)
{
	HANDLE _Console;
	_Console = GetStdHandle(STD_OUTPUT_HANDLE);


	CurrentTestCase = TestName;
	QueryPerformanceFrequency(&Frequency);
	switch (CurrentLogType)
	{
	case LogType::FULL:
		SetConsoleTextAttribute(_Console, FOREGROUND_WHITE);
		printf("Test Case: %s\n", CurrentTestCase);
		printf("------------------ \n");
		printf(
			"Benchmark Starting \n"
			"------------------ \n");

		SetConsoleTextAttribute(_Console, FOREGROUND_INTENSE_RED);
		printf(
			"Frequency Highpart: %li ticks\n"
			"Frequency Lowpart: %li ticks\n"
			"Frequency QuadPart: %I64d ticks\n"
			"Frequency union HighPart: %li ticks\n"
			"Frequency union LowPart: %li ticks\n"
			"\n",
			(long)Frequency.HighPart,
			(long)Frequency.LowPart,
			(__int64)Frequency.QuadPart,
			(long)Frequency.u.HighPart,
			(long)Frequency.u.LowPart);
		SetConsoleTextAttribute(_Console, BACKGROUND_INTENSE_WHITE|FOREGROUND_INTENSE_BLUE);
		printf("Counter Started...\n");
		break;
	case LogType::SHORT:
		SetConsoleTextAttribute(_Console, BACKGROUND_INTENSE_WHITE | FOREGROUND_INTENSE_RED);
		printf("Test Case: %s - Measuring...", TestName);
		break;
	default:break;
	}
	QueryPerformanceCounter(&StartCounter);
}

void CPUBenchmark::Stop()
{
	QueryPerformanceCounter(&EndCounter);



	LARGE_INTEGER ElaspedTime;
	ElaspedTime.QuadPart = (EndCounter.QuadPart - StartCounter.QuadPart);
	float seconds = ((ElaspedTime.QuadPart * 1000000) / Frequency.QuadPart) * 0.000001f;

	HANDLE _Console;
	_Console = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (CurrentLogType)
	{
	case LogType::FULL:
		SetConsoleTextAttribute(_Console, FOREGROUND_INTENSE_GREEN);
		printf(
			"Counter Ended.\n"
			"------------------\n"
			"Counter HighPart: %li ticks \n"
			"Counter LowPart: %li ticks \n"
			"Counter QuadPart: %I64d ticks \n"
			"Counter HighPart: %li ticks \n"
			"Counter LowPart: %li ticks \n\n"
			"Elasped Time(S): %f \n",
			(long)ElaspedTime.HighPart,
			(long)ElaspedTime.LowPart,
			(__int64)ElaspedTime.QuadPart,
			(long)ElaspedTime.u.HighPart,
			(long)ElaspedTime.u.LowPart,
			seconds);
		break;
	case LogType::SHORT:
		SetConsoleTextAttribute(_Console, FOREGROUND_INTENSE_GREEN);
		printf("\rTest Case: %s - %f(S) \n", CurrentTestCase, seconds);
		break;
	default:
		break;
	}

}

void CPUBenchmark::SetBenchmarkLogType(LogType NewLogType)
{
	CurrentLogType = NewLogType;
}
