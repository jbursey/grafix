#pragma once
#include <Windows.h>
#include <dxgi.h>
#include <d3d11.h>
#include "DeviceResources.h"

class Application
{
public:
	Application();
	void Init(HWND handle, int width, int height);
	bool Run();

	void ResizeWindow(int width, int height);

private:	
	DeviceResources* _resources;
	bool _appReady;
};

