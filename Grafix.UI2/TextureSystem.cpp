#include "TextureSystem.h"

void TextureSystem::Init(Graphics* graphics)
{	
	D3D11_SAMPLER_DESC sampleDesc;
	ZeroMemory(&sampleDesc, sizeof(D3D11_SAMPLER_DESC));
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;	

	graphics->Device->CreateSamplerState(&sampleDesc, &_samplerState);
	//graphics->Context->PSSetSamplers(0, 1)

	HRESULT result = DirectX::CreateDDSTextureFromFile(graphics->Device, L"", 0, 0, 0);

	int stop = 0;
}

void TextureSystem::Tick(Graphics* graphics)
{
	
}
