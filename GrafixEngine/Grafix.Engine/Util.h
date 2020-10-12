#pragma once
#include <DirectXMath.h>
#include <random>
#include "Perlin.h"
#include <Windows.h>

class Util
{
public:
	static DirectX::XMFLOAT4 CreateRandomColor();
	static void Test_DeleteMe_PerlinNoiseVisual();
private:
};
