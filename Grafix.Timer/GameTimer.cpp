#include "pch.h"
#include "GameTimer.h"

void GameTimer::Start()
{
	QueryPerformanceCounter(&_start);	
	QueryPerformanceCounter(&_then);
	QueryPerformanceFrequency(&_freq);
}

void GameTimer::Tick()
{
	//LARGE_INTEGER now;
	//QueryPerformanceCounter(&now);

	//double diff = (now.QuadPart - _then.QuadPart) / (_freq.QuadPart / (1000 * 1.0));

	//_then = now;
	
}

void GameTimer::Stop()
{
}

void GameTimer::Reset()
{
}

double GameTimer::ElapsedTimeMS()
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	double diff = (now.QuadPart - _then.QuadPart) / (_freq.QuadPart / (1000 * 1.0));

	_then = now;

	return diff;
}

double GameTimer::TotalTimeMS()
{
	return 0;
}
