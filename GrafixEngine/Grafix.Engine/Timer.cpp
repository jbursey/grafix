#include "Timer.h"

void Timer::Start()
{
	QueryPerformanceCounter(&_start);
	QueryPerformanceCounter(&_then);
	QueryPerformanceFrequency(&_freq);
}

double Timer::GetElapsedTimeMS()
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	double ms = (now.QuadPart - _then.QuadPart) / (_freq.QuadPart / 1000.0);	

	_then = now;

	return ms;
}



