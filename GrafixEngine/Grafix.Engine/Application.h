#pragma once
#include <Windows.h>
#include <dxgi.h>
#include <d3d11.h>
#include "DeviceResources.h"
#include "AssetCache.h"

class Application
{
public:	
	void Init(HWND handle, int width, int height);
	bool Run();
	void ResizeWindow(int width, int height);

	DeviceResources* Resources;
	AssetCache* AssetCache;

	static Application* Current();

private:	
	Application();	
	bool _appReady;

	

	static Application* _instance;
};

