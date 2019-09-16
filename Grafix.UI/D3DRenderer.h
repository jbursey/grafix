#pragma once
#include <Windows.h>
#include <d3d11.h>
#include <dxgi.h>
#include "ShaderManager.h"
#include "TriangleTest.h"
#include "Camera.h"

class D3DRenderer
{
public:
	void Init(HWND handle, int width, int height);
	void Update();
	void Render();
	void Resize(int width, int height);

private:
	IDXGIAdapter* _dxgiAdapter;
	IDXGIFactory* _dxgiFactory;
	IDXGISwapChain* _dxgiSwapChain;
	IDXGIDevice* _dxgiDevice;	
	ID3D11Device* _device;
	ID3D11DeviceContext* _context;
	ID3D11RenderTargetView* _rtv;
	ID3D11DepthStencilView* _dsv;

	ShaderManager _sm;
	TriangleTest _tt;
	Camera _camera;

	int _width;
	int _height;
};

