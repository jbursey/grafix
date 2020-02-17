#pragma once
#include <string>
#include "Structs.h"

class TerrainSystem
{
public:
	TerrainSystem();
	~TerrainSystem();
	void Init();
	void Update(PositionComponent position, bool snapToTerrain, bool allowOutOfBounds);
	double GetHeight(int x, int z);
};

