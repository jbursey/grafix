#include "D3DRenderer.h"

D3DRenderer::D3DRenderer()
{
	_swapChainCreated = false;
}

void D3DRenderer::Init(HWND handle, int width, int height)
{
	_width = width;
	_height = height;

	//--create the dxgi factory
	auto dxgihr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_dxgiFactory);

	//--get a handle for the main device....usually the graphics card
	auto dxgiadapterhr = _dxgiFactory->EnumAdapters(0, &_dxgiAdapter);

	DXGI_ADAPTER_DESC adapterDesc;
	_dxgiAdapter->GetDesc(&adapterDesc);

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

	_swapChainCreated = true;

	Resize(width, height);

	_sm.Init(_device);
	_tt.Init(_device);
	//_camera.Init(width, height, 1, 1000);
	_scene.Init(width, height, _device);

	int stop = 0;
}

void D3DRenderer::Update(InputControls* controls)
{
	if (controls->IsKeyDown('W'))
	{
		_scene.Camera.MoveForward();
	}
	if (controls->IsKeyDown('S'))
	{
		_scene.Camera.MoveBackward();
	}
	if (controls->IsKeyDown('D'))
	{
		_scene.Camera.TurnRight();
	}
	if (controls->IsKeyDown('A'))
	{
		_scene.Camera.TurnLeft();
	}
	if (controls->IsKeyDown('T'))
	{
		_scene.Camera.MoveUp();
	}
	if (controls->IsKeyDown('G'))
	{
		_scene.Camera.MoveDown();
	}
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
	//_tt.Render(_context);	
	_scene.Render(_context);
	_dxgiSwapChain->Present(0, 0);
}

void D3DRenderer::Resize(int width, int height)
{	
	if (_swapChainCreated)
	{
		if (_dsv)
		{
			_dsv->Release();
		}

		if (_rtv)
		{
			_rtv->Release();
		}

		if (_depthBuffer)
		{
			_depthBuffer->Release();
		}		

		ID3D11Texture2D* backBuffer;
		auto getBufferResult = _dxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		if (getBufferResult == S_OK)
		{
			if (backBuffer)
			{
				backBuffer->Release();
			}
		}
	
		auto resizeResult = _dxgiSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, 0);

		//-----

		//--create render target view			
		getBufferResult = _dxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)& backBuffer);
		auto rtvResult = _device->CreateRenderTargetView(backBuffer, nullptr, &_rtv);
		_context->OMSetRenderTargets(1, &_rtv, 0);		
		backBuffer->Release();

		//--create depth stencil view
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		ZeroMemory(&dsvDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		dsvDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvDesc.Texture2D.MipSlice = 0;

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
		auto depthBufferResult = _device->CreateTexture2D(&texDesc, 0, &_depthBuffer);

		auto dsvResult = _device->CreateDepthStencilView(_depthBuffer, &dsvDesc, &_dsv);		

		//--create viewport
		D3D11_VIEWPORT viewport;
		viewport.Height = height;
		viewport.MaxDepth = 1.0;
		viewport.MinDepth = 0;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = width;

		_context->RSSetViewports(1, &viewport);

		//-----

		_scene.Camera.Resize(width, height, 1, 1000);

		int sto = 0;
	}
}
