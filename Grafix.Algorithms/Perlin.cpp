#include "Perlin.h"

Perlin::Perlin()
{
}

Perlin::~Perlin()
{
}

void Perlin::Implement()
{
	//grid definition with random gradient vectors unit length
	int rows = 10;
	int cols = 10;
	for (int x = 0; x < rows; x++)
	{
		std::vector<Vec2d> row;
		for (int z = 0; z < cols; z++)
		{
			Vec2d v;
			v.x = (rand() * 65535) % 65535;
			v.y = (rand() * 65535) % 65535;
			row.push_back(v);
		}

		_grid.push_back(row);
	}

	//dot product

	//interpolation
}
