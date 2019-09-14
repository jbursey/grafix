#include "D3DRenderer.h"

void D3DRenderer::Init(HWND handle, int width, int height)
{
	_width = width;
	_height = height;

	//--create the dxgi factory
	auto dxgihr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_dxgiFactory);

	//--get a handle for the main device....usually the graphics card
	auto dxgiadapterhr = _dxgiFactory->EnumAdapters(0, &_dxgiAdapter);

	unsigned int deviceflags = 0;
	deviceflags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	deviceflags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL levels[1];
	levels[0] = D3D_FEATURE_LEVEL_11_0;
	
	DXGI_SWAP_CHAIN_DESC swapDesc;
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.Height = height;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING::DXGI_MODE_SCALING_STRETCHED;
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Width = width;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.Flags = 0;
	swapDesc.OutputWindow = handle;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Windowed = true;

	auto d3dresult = D3D11CreateDeviceAndSwapChain(_dxgiAdapter, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, 0, deviceflags, levels, 1, D3D11_SDK_VERSION, &swapDesc, &_dxgiSwapChain, &_device, 0, &_context);

	//--create render target view	
	ID3D11Texture2D* backBuffer;
	auto backBufferGetResult = _dxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)& backBuffer);
	auto rtvResult = _device->CreateRenderTargetView(backBuffer, nullptr, &_rtv);
	_context->OMSetRenderTargets(1, &_rtv, 0);

	//--create depth stencil view
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;	
	ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsvDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;	
	dsvDesc.Texture2D.MipSlice = 0;

	ID3D11Texture2D* depthBuffer;
	D3D11_TEXTURE2D_DESC texDesc;
	ZeroMemory(&texDesc, sizeof(texDesc));
	texDesc.ArraySize = 1;	
	texDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
	//texDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	texDesc.CPUAccessFlags = 0;
	texDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
	texDesc.Height = height;
	texDesc.MipLevels = 1;	
	texDesc.MiscFlags = 0;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
	texDesc.Width = width;
	auto depthBufferResult = _device->CreateTexture2D(&texDesc, 0, &depthBuffer);

	auto dsvResult = _device->CreateDepthStencilView(depthBuffer, &dsvDesc, &_dsv);	
	
	//--create viewport
	D3D11_VIEWPORT viewport;
	viewport.Height = height;
	viewport.MaxDepth = 1.0;
	viewport.MinDepth = 0;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = width;

	_context->RSSetViewports(1, &viewport);		
	D3D11_RASTERIZER_DESC rastDesc;
	ZeroMemory(&rastDesc, sizeof(D3D11_RASTERIZER_DESC));
	rastDesc.CullMode = D3D11_CULL_BACK;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	ID3D11RasterizerState* rastState;
	_device->CreateRasterizerState(&rastDesc, &rastState);
	_context->RSSetState(rastState);	
	
	_sm.Init(_device);
	_tt.Init(_device);

	int stop = 0;
}

void D3DRenderer::Update()
{
}

void D3DRenderer::Render()
{		
	static float red = 0;
	static float green = 0;
	static float blue = 0;
	//red = (rand() % 255) / 255.0;
	//green = (rand() % 255) / 255.0;
	//blue = (rand() % 255) / 255.0;

	float color[4];
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = 255;
	_context->ClearDepthStencilView(_dsv, D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH, 1.0, 0);	
	_context->ClearRenderTargetView(_rtv, &color[0]);
	_sm.Render(_context);
	_tt.Render(_context);	
	_dxgiSwapChain->Present(0, 0);
}

void D3DRenderer::Resize(int width, int height)
{
}
