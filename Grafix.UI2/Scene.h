#pragma once
#include "Structs.h"
#include "Graphics.h"
#include "GrafixConstants.h"
#include "RenderSystem.h"
#include "LightSystem.h"
#include "PhysicsSystem.h"
#include "TerrainSystem.h"
#include "AssetSystem.h"
#include "ShaderSystem.h"
#include "Camera.h"
#include "MeshUtil.h"
#include "InputControls.h"

class Scene
{
public:
	Scene();
	~Scene();
	void Init(HWND handle, int width, int height);
	void Resize(int width, int height);
	void Update(InputControls* controls);
	void Tick();

private:
	EntityData _entities;
	std::vector<Entity> _entities2;
	Graphics* _graphics;	
	RenderSystem _systemRender;
	LightSystem _systemLight;
	PhysicsSystem _systemPhysics;
	TerrainSystem _systemTerrain;
	AssetSystem _systemAsset;
	ShaderSystem _systemShader;
	Camera _camera;
};

