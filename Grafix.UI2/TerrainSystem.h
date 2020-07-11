#pragma once
#include <string>
#include <map>
#include "Structs.h"
#include "GrafixConstants.h"
#include "MeshUtil.h"

class TerrainSystem
{
public:
	TerrainSystem();
	~TerrainSystem();
	void Init(EntityData& entities, Mesh mesh);
	void Update(PositionComponent* position, bool snapToTerrain, bool allowOutOfBounds);
	double GetHeight(int x, int z);

private:
	Mesh _mesh;		
	//std::map<int, std::vector<int, double>> _heightCache;
};

