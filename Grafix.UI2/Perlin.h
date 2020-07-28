#pragma once
#include <DirectXMath.h>
#include <vector>
#include <time.h>

class Perlin
{
public:
	void Init(int width, int height);
	double Noise(double x, double y);

private:
	std::vector<DirectX::XMFLOAT2> _randomGradients;
	std::vector<DirectX::XMFLOAT2> _grid;

	double LerpAndSmooth(double start, double end, double factor);
	int GetGridVectorOffset(int x, int y);
	int _maxWidth;
	int _maxHeight;
};

