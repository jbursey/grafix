#pragma once
#include <vector>
#include <random>
#include <time.h>

struct Vec2d
{
public:
	Vec2d() : x(0), y(0)
	{

	}

	float x;
	float y;
};

class Perlin
{
public:
	Perlin();
	~Perlin();	
	void Implement(int x, int y);

private:
	std::vector<std::vector<Vec2d>> _grid;
	std::vector<double> GetDotProductsWithCorners(double perlinX, double perlinY);
	double Lerp(double perlinX, double perlinY, std::vector<double> dots);
};

