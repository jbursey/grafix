#pragma once
class Perlin
{
public:
	double Init(int width, int height, int maxWidth, int maxHeight);
	double Noise(double x, double y);
};

