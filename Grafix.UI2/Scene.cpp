#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::Init(HWND handle, int width, int height)
{
	//--setup the d3d stuff
	_graphics.Init(handle, width, height);

	//--struct of arrays
	_entities.LightComponents.resize(GrafixConstants::MaxEntities);
	_entities.PositionComponents.resize(GrafixConstants::MaxEntities);
	_entities.PhysicsComponents.resize(GrafixConstants::MaxEntities);
	_entities.RenderComponents.resize(GrafixConstants::MaxEntities);

	//--systems init
	_systemAsset.Init();

}

void Scene::Resize(int width, int height)
{
	_graphics.Resize(width, height);
}

void Scene::Update()
{
	/*for (int i = 0; i < GrafixConstants::MaxEntities; i++)
	{
		_systemTerrain
	}*/
}

void Scene::Tick()
{
	_graphics.Tick();
}
