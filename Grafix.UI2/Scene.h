#pragma once
#include "Structs.h"
#include "Graphics.h"
#include "GrafixConstantsh.h"
#include "RenderSystem.h"
#include "LightSystem.h"
#include "PhysicsSystem.h"
#include "TerrainSystem.h"
#include "AssetSystem.h"

class Scene
{
public:
	Scene();
	~Scene();
	void Init(HWND handle, int width, int height);
	void Resize(int width, int height);
	void Update();
	void Tick();

private:
	EntityData _entities;
	Graphics _graphics;	
	RenderSystem _systemRender;
	LightSystem _systemLight;
	PhysicsSystem _systemPhysics;
	TerrainSystem _systemTerrain;
	AssetSystem _systemAsset;
};

