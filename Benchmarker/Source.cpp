#pragma once
#include "CPUBenchmark.h"
#include <iostream>
#include <random>
int main()
{
	//if (false)
	{

		CPUBenchmark tester;
		int high = 100000000;

		int low = high * 0.5f;
		tester.SetBenchmarkLogType(LogType::SHORT);
		for (int i = 0; i < 100; ++i)
		{
			int max = rand() % low + high;
			char Name[20] = "Test ";

			char cInt[20];
			_itoa_s(max, cInt, 20, 10);
			strcat_s(Name,sizeof(Name), cInt);

			tester.Start(Name);
			for (int j = 0; j < max; ++j);
			tester.Stop();
		}
	}

	std::getchar();
	return 0;
}