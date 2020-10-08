#include "Application.h"

void Application::Init()
{

}

bool Application::Run()
{
	MSG msg;
	bool isRunning = true;

	while (isRunning)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//--game system update

		//--game system tick
	}

	return isRunning;
}
