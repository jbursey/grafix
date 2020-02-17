#pragma once
#include <d3d11.h>

class Graphics
{
public:
	Graphics();
	~Graphics();
	void Init(HWND hwnd, int width, int height);
	void Resize(int width, int height);
	void Tick();

	ID3D11Device* Device;
	ID3D11DeviceContext* Context;	

private:
	bool _swapChainCreated;
	IDXGIAdapter* DxgiAdapter;
	IDXGIFactory* DxgiFactory;
	IDXGISwapChain* DxgiSwapChain;
	IDXGIDevice* DxgiDevice;
	ID3D11RenderTargetView* Rtv;
	ID3D11DepthStencilView* Dsv;
	ID3D11Texture2D* DepthBuffer;
};

