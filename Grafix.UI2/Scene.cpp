#include "Scene.h"



Scene::Scene()
{
	_graphics = new Graphics();
}


Scene::~Scene()
{
}

void Scene::Init(HWND handle, int width, int height)
{
	//--setup the d3d stuff	
	_graphics->Init(handle, width, height);
	_camera.Init(width, height, 1.0, 5000.0);

	//--struct of arrays
	_entities.LightComponents.resize(GrafixConstants::MaxEntities);
	_entities.PositionComponents.resize(GrafixConstants::MaxEntities);
	_entities.PhysicsComponents.resize(GrafixConstants::MaxEntities);
	_entities.RenderComponents.resize(GrafixConstants::MaxEntities);

	//--systems init
	_systemAsset.Init();
	_systemShader.Init(&_systemAsset);

	//--turn all components off
	for (int i = 0; i < GrafixConstants::MaxEntities; i++)
	{
		_entities.LightComponents[i] = 0;
		_entities.PhysicsComponents[i] = 0;
		_entities.PositionComponents[i] = 0;
		_entities.RenderComponents[i] = 0;
	}

	//--make some entities	
	_entities.RenderComponents[0] = new RenderComponent();
	_entities.RenderComponents[0]->CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	_entities.RenderComponents[0]->FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	//_entities.RenderComponents[0].Mesh = MeshUtil::GetSphere(5.0, 10, 20);
	_entities.RenderComponents[0]->Mesh = MeshUtil::GetGrid(_systemAsset.GetAsset("usgs_colo_springs.bmp"), 1.0);
	_entities.RenderComponents[0]->PixelShader = "PixelShader.cso";
	_entities.RenderComponents[0]->Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	_entities.RenderComponents[0]->VertexShader = "VertexShader.cso";
	
	_entities.PositionComponents[0] = new PositionComponent();
	_entities.PositionComponents[0]->Pitch = 0;
	_entities.PositionComponents[0]->Roll = 0;
	_entities.PositionComponents[0]->Yaw = 0;
	_entities.PositionComponents[0]->X = 0;
	_entities.PositionComponents[0]->Y = 0;
	_entities.PositionComponents[0]->Z = 20;
}

void Scene::Resize(int width, int height)
{
	_graphics->Resize(width, height);
	_camera.Resize(width, height, 1.0, 5000.0);
}

void Scene::Update(InputControls* controls)
{

	if (controls->IsKeyDown('W'))
	{
		_camera.MoveForward();
	}
	if (controls->IsKeyDown('S'))
	{
		_camera.MoveBackward();
	}
	if (controls->IsKeyDown('D'))
	{
		_camera.TurnRight();
	}
	if (controls->IsKeyDown('A'))
	{
		_camera.TurnLeft();
	}
	if (controls->IsKeyDown('T'))
	{
		_camera.MoveUp();
	}
	if (controls->IsKeyDown('G'))
	{
		_camera.MoveDown();
	}

	//_scene.Lights.Update();

	/*for (int i = 0; i < GrafixConstants::MaxEntities; i++)
	{
		_systemTerrain
	}*/
}

void Scene::Tick()
{
	_graphics->BeginDraw();

	////-- system ticks?
	//for (Entity e : _entities2)
	//{
	//	if (e.Render && e.Position)
	//	{
	//		_systemRender.Tick(e.ID, *e.Render, *e.Position, _graphics, _camera);
	//	}
	//}
	for (int i = 0; i < GrafixConstants::MaxEntities; i++)
	{
		_systemShader.Tick(_entities.RenderComponents[i], _graphics);
	}

	for (int i = 0; i < GrafixConstants::MaxEntities; i++)
	{
		_systemRender.Tick(i, _entities.RenderComponents[i], _entities.PositionComponents[i], _graphics, _camera);
	}

	_graphics->EndDraw();
}
