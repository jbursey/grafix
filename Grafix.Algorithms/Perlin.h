#pragma once
#include <vector>
#include <random>

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
	void Implement();

private:
	std::vector<std::vector<Vec2d>> _grid;
};

