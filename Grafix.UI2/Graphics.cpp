#include "Graphics.h"

Graphics::Graphics()
{
	_swapChainCreated = false;
}

Graphics::~Graphics()
{
}

void Graphics::Init(HWND hwnd, int width, int height)
{
	//_width = width;
	//_height = height;

	//--create the dxgi factory
	auto dxgihr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)& DxgiFactory);

	//--get a handle for the main device....usually the graphics card
	auto dxgiadapterhr = DxgiFactory->EnumAdapters(0, &DxgiAdapter);

	DXGI_ADAPTER_DESC adapterDesc;
	DxgiAdapter->GetDesc(&adapterDesc);

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
	swapDesc.OutputWindow = hwnd;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Windowed = true;

	auto d3dresult = D3D11CreateDeviceAndSwapChain(DxgiAdapter, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, 0, deviceflags, levels, 1, D3D11_SDK_VERSION, &swapDesc, &DxgiSwapChain, &Device, 0, &Context);

	_swapChainCreated = true;

	Resize(width, height);

	/*_sm.Init(_device);
	_tt.Init(_device);	
	_scene.Init(width, height, _device);*/

	//if (false)
	//{
	//	Entity normalEntity;
	//	Mesh normalLine;
	//	//std::vector<Entity> normalEntities;
	//	int normalEntityIndex = 0;
	//	for (int i = 0; i < _scene.Entities.size(); i++)
	//	{
	//		Entity& e = _scene.Entities[i];
	//		Mesh m = e.GetMesh();

	//		for (int j = 0; j < m.Vertx.size(); j++)
	//		{
	//			Vertex v = m.Vertx[j];

	//			Vertex start;
	//			Vertex end;

	//			start.Point = DirectX::XMFLOAT4(v.Point.x, v.Point.y, v.Point.z, 1);
	//			start.Color = DirectX::XMFLOAT4(1, 0, 0, 1);

	//			end.Point = DirectX::XMFLOAT4(v.Point.x + v.Normal.x, v.Point.y + v.Normal.y, v.Point.z + v.Normal.z, 1);
	//			end.Color = DirectX::XMFLOAT4(1, 0, 0, 1);

	//			normalLine.Vertx.push_back(start);
	//			normalLine.Vertx.push_back(end);

	//			normalLine.Indx.push_back(normalEntityIndex++);
	//			normalLine.Indx.push_back(normalEntityIndex++);

	//		}

	//		//if (i == 3)
	//		//{
	//		//	break;
	//		//}
	//	}

		//normalEntity.Init(normalLine, _device);
		////normalEntity.SetPosition(start.Point.x, start.Point.y, start.Point.z);
		//normalEntity.SetPosition(0, 0, 0);
		//normalEntity.SetOrientation(0, 0, 0);
		//normalEntity.SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		//_scene.AddEntity(normalEntity);
	//}

	int stop = 0;
}

void Graphics::Resize(int width, int height)
{
	if (_swapChainCreated)
	{
		if (Dsv)
		{
			Dsv->Release();
		}

		if (Rtv)
		{
			Rtv->Release();
		}

		if (DepthBuffer)
		{
			DepthBuffer->Release();
		}

		ID3D11Texture2D* backBuffer;
		auto getBufferResult = DxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)& backBuffer);
		if (getBufferResult == S_OK)
		{
			if (backBuffer)
			{
				backBuffer->Release();
			}
		}

		auto resizeResult = DxgiSwapChain->ResizeBuffers(1, width, height, DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM, 0);

		//-----

		//--create render target view			
		getBufferResult = DxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)& backBuffer);
		auto rtvResult = Device->CreateRenderTargetView(backBuffer, nullptr, &Rtv);
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
		auto depthBufferResult = Device->CreateTexture2D(&texDesc, 0, &DepthBuffer);

		auto dsvResult = Device->CreateDepthStencilView(DepthBuffer, &dsvDesc, &Dsv);

		Context->OMSetRenderTargets(1, &Rtv, Dsv);

		//--create viewport
		D3D11_VIEWPORT viewport;
		viewport.Height = height;
		viewport.MaxDepth = 1.0;
		viewport.MinDepth = 0;
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = width;

		Context->RSSetViewports(1, &viewport);

		//-----

		//_scene.Camera.Resize(width, height, 1, 2000);

		int sto = 0;
	}
}

void Graphics::BeginDraw()
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
	Context->ClearDepthStencilView(Dsv, D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH, 1.0, 0);
	Context->ClearRenderTargetView(Rtv, &color[0]);
	//_sm.Render(_context);
	//_tt.Render(_context);	
	//_scene.Render(_context);	
}

void Graphics::EndDraw()
{

	DxgiSwapChain->Present(0, 0);
}
