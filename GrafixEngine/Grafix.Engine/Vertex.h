#pragma once
#include <DirectXMath.h>

struct Vertex
{
public:
	DirectX::XMFLOAT4 Point;
	DirectX::XMFLOAT4 Color;
	DirectX::XMFLOAT4 Normal;
	DirectX::XMFLOAT2 TexUV;
};

