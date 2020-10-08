#include "main.h"
#include <iostream>
#include <thread>
#include <random>
#include <time.h>

// engine imports
#include "GrafixEngine.h"

using namespace std;

int main(int argv, char** args)
{
	cout << "Hello World" << endl;

	srand(time(0));

	Timer t;
	t.Start();

	for (int i = 0; i < 5; i++)
	{
		int ranMs = rand() % 2000;		
		cout << "Sleeping for " << ranMs << " ms" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(ranMs));
		double ms = t.GetElapsedTimeMS();
		cout << "Ms: " << ms << endl;
	}

	//constant sleep of 1000ms	
	for (int i = 0; i < 5; i++)
	{		
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		Sleep(30);
		double ms = t.GetElapsedTimeMS();

		cout << "Ms: " << ms << endl;
	}

	//constants output
	cout << "MILLISECONDS_PER_UPDATE: " << Grafix::MILLISECONDS_PER_UPDATE << endl;
	cout << "W_POINT: " << Grafix::W_POINT << endl;
	cout << "W_VECTOR: " << Grafix::W_VECTOR << endl;


	return 0;
}