#pragma once
#include "Structs.h"
#include "Graphics.h"
#include <DDSTextureLoader.h>

class TextureSystem
{
public:
	void Init(Graphics* graphics);
	void Tick(Graphics* graphics);
private:
	ID3D11SamplerState* _samplerState;
};

