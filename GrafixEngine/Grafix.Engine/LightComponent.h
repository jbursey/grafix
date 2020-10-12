#pragma once
#include <DirectXMath.h>

struct LightComponent
{

public:
	double PosX;
	double PosY;
	double PosZ;

	DirectX::XMFLOAT4 Color;

	double AttenuationConstant;
	double AttenuationLinear;
	double AttenuationPoly;

private:


};