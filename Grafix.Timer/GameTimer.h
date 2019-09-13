#pragma once
#include <Windows.h>
class GameTimer
{
public:
	void Start();
	void Tick();
	void Pause();
	void Stop();
	void Reset();
	double ElapsedTimeMS();
	double TotalTimeMS();
private:	
	LARGE_INTEGER _start;
	LARGE_INTEGER _stop;
	LARGE_INTEGER _freq;
	LARGE_INTEGER _then;
protected:
};

