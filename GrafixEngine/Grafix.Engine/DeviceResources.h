#pragma once
#include <d3d11.h>
#include <dxgi.h>

struct DeviceResources
{
public:
	//DirectX
	ID3D11Device* Device;
	ID3D11DeviceContext* Context;
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11DepthStencilView* DepthStencilView;
	ID3D11Texture2D* DepthTexture;

	//DXGI
	IDXGIAdapter* Adapter;
	IDXGIFactory* DXGIFactory;
	IDXGISwapChain* SwapChain;

	//?
};
