#include "TerrainSystem.h"



TerrainSystem::TerrainSystem()
{
}


TerrainSystem::~TerrainSystem()
{
}

void TerrainSystem::Init(EntityData& entities, Mesh mesh)
{		
	_mesh = mesh;	

	////height cache? make better
	//for (Vertex v : _mesh.Vertx)
	//{
	//	auto what = _heightCache.find((int)v.Point.x);

	//	int stop = 0;;
	//}

	entities.RenderComponents[GrafixConstants::EntityTerrainID] = new RenderComponent();
	entities.RenderComponents[GrafixConstants::EntityTerrainID]->CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	entities.RenderComponents[GrafixConstants::EntityTerrainID]->FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	entities.RenderComponents[GrafixConstants::EntityTerrainID]->Mesh = _mesh;
	entities.RenderComponents[GrafixConstants::EntityTerrainID]->PixelShader = "PixelShaderTexture.cso";
	entities.RenderComponents[GrafixConstants::EntityTerrainID]->Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	entities.RenderComponents[GrafixConstants::EntityTerrainID]->VertexShader = "VertexShader.cso";

	entities.PositionComponents[GrafixConstants::EntityTerrainID] = new PositionComponent();	
	entities.PositionComponents[GrafixConstants::EntityTerrainID]->Pitch = 0;
	entities.PositionComponents[GrafixConstants::EntityTerrainID]->Roll = 0;
	entities.PositionComponents[GrafixConstants::EntityTerrainID]->Yaw = 0;
	entities.PositionComponents[GrafixConstants::EntityTerrainID]->X = 0;
	entities.PositionComponents[GrafixConstants::EntityTerrainID]->Y = 0;		
}

void TerrainSystem::Update(PositionComponent* position, bool snapToTerrain, bool allowOutOfBounds)
{
	if (!position)
	{
		return;
	}	

	if (snapToTerrain)
	{
		double y = GetHeight(position->X, position->Z);
		position->Y = y;
	}

	if (!allowOutOfBounds)
	{
		//
	}
}

double TerrainSystem::GetHeight(int entX, int entZ)
{
	for (Vertex v : _mesh.Vertx)
	{
		if (v.Point.x == entX && v.Point.z == entZ)
		{
			return v.Point.y;
		}
	}

	return 0;
}
