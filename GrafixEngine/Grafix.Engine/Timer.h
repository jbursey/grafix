#pragma once
#include <Windows.h>

class Timer
{
public:
	void Start();	
	double GetElapsedTimeMS();
private:
	LARGE_INTEGER _start;
	LARGE_INTEGER _end;
	LARGE_INTEGER _then;
	LARGE_INTEGER _freq;	
	
};

