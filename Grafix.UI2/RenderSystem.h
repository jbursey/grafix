#pragma once
#include <d3d11.h>
#include <dxgi.h>

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();
	void Render();

private: 
	IDXGIAdapter* _dxgiAdapter;
	IDXGIFactory* _dxgiFactory;
	IDXGISwapChain* _dxgiSwapChain;
	IDXGIDevice* _dxgiDevice;
	ID3D11Device* _device;
	ID3D11DeviceContext* _context;
	ID3D11RenderTargetView* _rtv;
	ID3D11DepthStencilView* _dsv;
	ID3D11Texture2D* _depthBuffer;
};

