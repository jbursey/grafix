#pragma once
#include "Structs.h"
#include "Graphics.h"
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>

class TextureSystem
{
public:
	void Init(Graphics* graphics);
	void Tick(Graphics* graphics);
private:
	ID3D11SamplerState* _samplerState;
	ID3D11ShaderResourceView* _srv;
	ID3D11Resource* _pngTexture;
};

