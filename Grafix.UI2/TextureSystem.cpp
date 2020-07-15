#include "TextureSystem.h"

void TextureSystem::Init(Graphics* graphics)
{	
	D3D11_SAMPLER_DESC sampleDesc;
	ZeroMemory(&sampleDesc, sizeof(D3D11_SAMPLER_DESC));
	sampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	sampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;	

	HRESULT createSamplerStateResult = graphics->Device->CreateSamplerState(&sampleDesc, &_samplerState);
	HRESULT createResult = DirectX::CreateWICTextureFromFile(graphics->Device, L"../../TestTexture.png", &_pngTexture, &_srv);
	

	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	_srv->GetDesc(&srvDesc);	

	int stop = 0;
}

void TextureSystem::Tick(Graphics* graphics)
{
	graphics->Context->PSSetShaderResources(0, 1, &_srv);
	graphics->Context->PSSetSamplers(0, 1, &_samplerState);
}
