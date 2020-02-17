#include "TerrainSystem.h"



TerrainSystem::TerrainSystem()
{
}


TerrainSystem::~TerrainSystem()
{
}

void TerrainSystem::Update(PositionComponent position, bool snapToTerrain, bool allowOutOfBounds)
{
	double y = GetHeight(position.X, position.Y);

	if (snapToTerrain)
	{
		position.Y = y;
	}

	if (!allowOutOfBounds)
	{
		//
	}
}

double TerrainSystem::GetHeight(int x, int z)
{
	return 0.0;
}
