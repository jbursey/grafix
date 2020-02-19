#include "Perlin.h"

Perlin::Perlin()
{
}

Perlin::~Perlin()
{
}

void Perlin::Implement(int x, int y)
{
	srand(time(0));

	//grid definition with random gradient vectors unit length
	int rows = 10;
	int cols = 10;	
	for (int x = 0; x < rows; x++)
	{
		std::vector<Vec2d> row;
		for (int z = 0; z < cols; z++)
		{
			Vec2d v;
			v.x = (rand() % 100000) / 100000.0;
			v.y = (rand() % 100000) / 100000.0;
			row.push_back(v);
		}

		_grid.push_back(row);
	}

	//dot product given a cordinate x,y
	//int X = 35;
	//int Y = 12;
	int MAX_X = 100;
	int MAX_Y = 100;

	/*
	
	x =>  35     X
	     ---- = ----
		 100     10

	x => X = (x * rows) / maxX

	*/

	double perlinX = (x * (rows - 1)) / (MAX_X * 1.0);
	double perlinY = (y * (cols - 1)) / (MAX_Y * 1.0);
	
	std::vector<double> dotProducts = GetDotProductsWithCorners(perlinX, perlinY);
	
	//interpolation
	double val = Lerp(perlinX, perlinY, dotProducts);	
}

std::vector<double> Perlin::GetDotProductsWithCorners(double perlinX, double perlinY)
{
	int x = floor(perlinX);
	int y = floor(perlinX);

	Vec2d v1 = _grid[x][y];
	Vec2d v2 = _grid[x+1][y];
	Vec2d v3 = _grid[x][y+1];
	Vec2d v4 = _grid[x+1][y+1];

	std::vector<Vec2d> vecs;
	vecs.push_back(v1);
	vecs.push_back(v2);
	vecs.push_back(v3);
	vecs.push_back(v4);

	Vec2d dirV1;
	dirV1.x = v1.x - perlinX;
	dirV1.y = v1.y - perlinY;

	Vec2d dirV2;
	dirV2.x = v2.x - perlinX;
	dirV2.y = v2.y - perlinY;

	Vec2d dirV3;
	dirV3.x = v3.x - perlinX;
	dirV3.y = v3.y - perlinY;

	Vec2d dirV4;
	dirV4.x = v4.x - perlinX;
	dirV4.y = v4.y - perlinY;

	double dotV1 = (dirV1.x * v1.x) + (dirV1.y * v1.y);
	double dotV2 = (dirV2.x * v2.x) + (dirV2.y * v2.y);
	double dotV3 = (dirV3.x * v3.x) + (dirV3.y * v3.y);
	double dotV4 = (dirV4.x * v4.x) + (dirV4.y * v4.y);

	std::vector<double> dotProducts;
	dotProducts.push_back(dotV1);
	dotProducts.push_back(dotV2);
	dotProducts.push_back(dotV3);
	dotProducts.push_back(dotV4);

	return dotProducts;
}

double Perlin::Lerp(double perlinX, double perlinY, std::vector<double> dots)
{
	double d0 = dots[0];
	double d1 = dots[1];
	double d2 = dots[2];
	double d3 = dots[3];

	return 0;
}
