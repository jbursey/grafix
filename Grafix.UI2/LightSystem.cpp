#include "LightSystem.h"



LightSystem::LightSystem()
{
}


LightSystem::~LightSystem()
{
}

void LightSystem::Init(Graphics* graphics)
{
	//_currentLightIndex = 0;

	//for (int i = 0; i < GrafixConstants::NumLights; i++)
	//{
	//	_cbPerFrame.pointLightColors[i] = DirectX::XMFLOAT4(0, 0, 0, 1);
	//	_cbPerFrame.pointLightPositions[i] = DirectX::XMFLOAT4(0, 0, 0, 1);
	//}

	D3D11_BUFFER_DESC cbDesc;
	cbDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.ByteWidth = sizeof(CBPerFrame);
	cbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	cbDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

	auto createBufferResult = graphics->Device->CreateBuffer(&cbDesc, 0, &_buffer);
}

void LightSystem::Update(int entityId, PositionComponent* pc, LightComponent* lc, Graphics* graphics)
{
	if (!pc)
	{
		return;
	}

	if (!lc)
	{
		return;
	}

	pc->X += 0.01;
	//pc->Y += 0.001;
	//lc->Color.x = pc->X / 255.0;
	//lc->Color.y = pc->Y / 255.0;
	//lc->Color.z = pc->X / 255.0;
	//

	LightPoint lp;
	lp.Position = DirectX::XMFLOAT4(pc->X, pc->Y, pc->Z, 1);
	lp.Color = lc->Color;
	lp.ConstantFactor = lc->AttenA;
	lp.LinearFactor = lc->AttenB;
	lp.SquareFactor = lc->AttenC;
	
	_lightPointsThisFrame.insert_or_assign(entityId, lp);
}

void LightSystem::Tick(Graphics* graphics)
{	
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	graphics->Context->Map(_buffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	mappedResource.DepthPitch = 0;
	mappedResource.RowPitch = 0;
	CBPerFrame* cbPerFrame = (CBPerFrame*)mappedResource.pData;
	int lightIndex = 0;
	for (std::pair<int, LightPoint> item : _lightPointsThisFrame)
	{
		if (lightIndex >= GrafixConstants::NumLights)
		{
			break;
		}

		cbPerFrame->pointLightColors[lightIndex] = item.second.Color;
		cbPerFrame->pointLightPositions[lightIndex] = item.second.Position;
		cbPerFrame->pointLightConstantFactor[lightIndex].x = item.second.ConstantFactor;
		cbPerFrame->pointLightLinearFactor[lightIndex].x = item.second.LinearFactor;
		cbPerFrame->pointLightSquareFactor[lightIndex].x = item.second.SquareFactor;
		++lightIndex;
	}
	graphics->Context->Unmap(_buffer, 0);

	graphics->Context->PSSetConstantBuffers(1, 1, &_buffer);
	_lightPointsThisFrame.clear();
}
