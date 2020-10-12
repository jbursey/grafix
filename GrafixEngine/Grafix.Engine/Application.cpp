#include "Application.h"

Application::Application()
{
	Resources = nullptr;
	_appReady = false;
}

void Application::Init(HWND handle, int width, int height)
{
	_appReady = false;
	Resources = new DeviceResources();

	//create factory
	HRESULT dxgiFactoryResult = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Resources->DXGIFactory);

	//create adapter
	HRESULT dxgiAdapterResult = Resources->DXGIFactory->EnumAdapters(0, &Resources->Adapter);

	//create device swap chain
	unsigned int deviceFlags = 0;
	deviceFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	D3D_FEATURE_LEVEL levels = {D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0};

	DXGI_SWAP_CHAIN_DESC swapDesc;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferCount = 1;
	swapDesc.BufferDesc.Width = width;
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

	HRESULT createDeviceResult = D3D11CreateDeviceAndSwapChain(Resources->Adapter, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, 0, deviceFlags, &levels, 1, D3D11_SDK_VERSION, 
		&swapDesc, &Resources->SwapChain, &Resources->Device, nullptr, &Resources->Context);

	_appReady = true;
	
	ResizeWindow(width, height);	
}

bool Application::Run()
{
	float bg[4] = {0,0,0,255};
	Resources->Context->ClearRenderTargetView(Resources->RenderTargetView, bg);
	Resources->Context->ClearDepthStencilView(Resources->DepthStencilView, D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH, 1.0, 0);

	//--other things here

	Resources->SwapChain->Present(0, 0);

	return true;
}

void Application::ResizeWindow(int width, int height)
{
	if (_appReady)
	{
		//resize back buffers
		ID3D11Texture2D* backBuffer = nullptr;
		HRESULT getBackBufferResult = Resources->SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);

		//create render target view
		if (Resources->DepthStencilView)
		{
			Resources->DepthStencilView->Release();
			Resources->DepthStencilView = 0;
		}

		if (Resources->DepthTexture)
		{
			Resources->DepthTexture->Release();
			Resources->DepthTexture = 0;
		}

		if (Resources->RenderTargetView)
		{
			Resources->RenderTargetView->Release();			
			Resources->RenderTargetView = 0;
		}

		if (backBuffer)
		{
			backBuffer->Release();
			backBuffer = 0;
		}	

		Resources->SwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, 0);

		////////////ID3D11Debug* debug = nullptr;
		////////////Resources->Device->QueryInterface(__uuidof(ID3D11Debug), (void**)&debug);

		////////////debug->ReportLiveDeviceObjects(D3D11_RLDO_FLAGS::D3D11_RLDO_DETAIL);
		////////////debug->Release();

		Resources->SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		ZeroMemory(&renderTargetDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		renderTargetDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;

		HRESULT createRTVResult = Resources->Device->CreateRenderTargetView(backBuffer, nullptr, &Resources->RenderTargetView);

		if (backBuffer)
		{
			backBuffer->Release();
		}

		//create depth stencil view
		D3D11_TEXTURE2D_DESC depthTextureDesc;
		depthTextureDesc.ArraySize = 1;
		depthTextureDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthTextureDesc.CPUAccessFlags = 0;
		depthTextureDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTextureDesc.Height = height;
		depthTextureDesc.MipLevels = 1;
		depthTextureDesc.MiscFlags = 0;
		depthTextureDesc.SampleDesc.Count = 1;
		depthTextureDesc.SampleDesc.Quality = 0;
		depthTextureDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthTextureDesc.Width = width;

		Resources->Device->CreateTexture2D(&depthTextureDesc, nullptr, &Resources->DepthTexture);

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

		HRESULT createDSVResult = Resources->Device->CreateDepthStencilView(Resources->DepthTexture, nullptr, &Resources->DepthStencilView);

		Resources->Context->OMSetRenderTargets(1, &Resources->RenderTargetView, Resources->DepthStencilView);

		//--create viewport
		D3D11_VIEWPORT viewport;
		viewport.Height = height;
		viewport.MaxDepth = 1.0;
		viewport.MinDepth = 0;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = width;

		Resources->Context->RSSetViewports(1, &viewport);
	}
}

Application* Application::Current()
{
	if (_instance == nullptr)
	{
		_instance = new Application();
	}

	return _instance;
}
