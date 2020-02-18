#include "LightSystem.h"



LightSystem::LightSystem()
{
}


LightSystem::~LightSystem()
{
}

void LightSystem::Init(Graphics* graphics)
{
	_currentLightIndex = 0;

	for (int i = 0; i < GrafixConstants::NumLights; i++)
	{
		_cbPerFrame.pointLightColors[i] = DirectX::XMFLOAT4(0, 0, 0, 1);
		_cbPerFrame.pointLightPositions[i] = DirectX::XMFLOAT4(0, 0, 0, 1);
	}

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.ByteWidth = sizeof(CBPerFrame);
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	cbDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

	auto createBufferResult = graphics->Device->CreateBuffer(&cbDesc, 0, &_buffer);
}

void LightSystem::Update(PositionComponent* pc, LightComponent* lc, Graphics* graphics)
{
	if (!pc)
	{
		return;
	}

	if (!lc)
	{
		return;
	}
	
	_cbPerFrame.pointLightColors[_currentLightIndex] = lc->Color;
	_cbPerFrame.pointLightPositions[_currentLightIndex] = DirectX::XMFLOAT4(pc->X, pc->Y, pc->Z, 1);

	++_currentLightIndex;
	if (_currentLightIndex >= GrafixConstants::NumLights)
	{
		_currentLightIndex = GrafixConstants::NumLights;
	}
}

void LightSystem::Tick(PositionComponent* pc, LightComponent* lc, Graphics* graphics)
{
	if (!pc)
	{
		return;
	}

	if (!lc)
	{
		return;
	}

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	graphics->Context->Map(_buffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	mappedResource.DepthPitch = 0;
	mappedResource.RowPitch = 0;
	CBPerFrame* cbPerFrame = (CBPerFrame*)mappedResource.pData;
	for (int i = 0; i < GrafixConstants::NumLights; i++)
	{
		cbPerFrame->pointLightColors[i] = _cbPerFrame.pointLightColors[i];
		cbPerFrame->pointLightPositions[i] = _cbPerFrame.pointLightPositions[i];
	}
	graphics->Context->Unmap(_buffer, 0);

	graphics->Context->PSSetConstantBuffers(1, 1, &_buffer);	

	_currentLightIndex = 0;
}
