#include "LightSystem.h"

LightSystem::LightSystem()
{
}

void LightSystem::Init(ID3D11Device* device)
{
	double y = 200;
	for (int i = 0; i < GrafixConstants::NumLights; i++)
	{		
		Lights.pointLightPositions[i] = DirectX::XMFLOAT4(i * 40, y, i * 40, 1);
		//_cbPerFrame.pointLightColors[i] = DirectX::XMFLOAT4(255, 0, 0, 1);
		Lights.pointLightColors[i] = Util::CreateRandomColor();

		y = y - 3;
	}	

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.ByteWidth = sizeof(CBPerFrame);
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	cbDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

	auto createBufferResult = device->CreateBuffer(&cbDesc, 0, &_buffer);
}

void LightSystem::Update()
{
	for (int i = 0; i < GrafixConstants::NumLights; i++)
	{
		//Lights.pointLightPositions[i] = DirectX::XMFLOAT4(i * 20, 0, i * 20, 1);
		Lights.pointLightPositions[i].x += 0.1;
		//_cbPerFrame.pointLightColors[i] = DirectX::XMFLOAT4(255, 0, 0, 1);
		//Lights.pointLightColors[i] = Util::CreateRandomColor();
	}
}

void LightSystem::Render(ID3D11DeviceContext* context)
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	context->Map(_buffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	mappedResource.DepthPitch = 0;
	mappedResource.RowPitch = 0;
	CBPerFrame* cbPerFrame = (CBPerFrame*)mappedResource.pData;
	for (int i = 0; i < GrafixConstants::NumLights; i++)
	{
		cbPerFrame->pointLightColors[i] = Lights.pointLightColors[i];
		cbPerFrame->pointLightPositions[i] = Lights.pointLightPositions[i];
	}	
	context->Unmap(_buffer, 0);

	context->PSSetConstantBuffers(1, 1, &_buffer);
}
