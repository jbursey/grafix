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
	_systemLight.Init(_graphics);

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
	_entities.RenderComponents[0]->Mesh = MeshUtil::GetGrid(_systemAsset.GetAsset("heightmap_test.bmp"), 1.0 / 6.0);
	_entities.RenderComponents[0]->PixelShader = "PixelShaderLights.cso";
	_entities.RenderComponents[0]->Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	_entities.RenderComponents[0]->VertexShader = "VertexShaderLights.cso";
	
	_entities.PositionComponents[0] = new PositionComponent();
	_entities.PositionComponents[0]->Pitch = 0;
	_entities.PositionComponents[0]->Roll = 0;
	_entities.PositionComponents[0]->Yaw = 0;
	_entities.PositionComponents[0]->X = 0;
	_entities.PositionComponents[0]->Y = 0;
	_entities.PositionComponents[0]->Z = 0;

	_entities.RenderComponents[1] = new RenderComponent();
	_entities.RenderComponents[1]->CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	_entities.RenderComponents[1]->FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	_entities.RenderComponents[1]->Mesh = MeshUtil::GetSphere(5.0, 30, 30);	
	_entities.RenderComponents[1]->Mesh.SetColor(1, 0, 0, 1);
	_entities.RenderComponents[1]->PixelShader = "PixelShader.cso";
	_entities.RenderComponents[1]->Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	_entities.RenderComponents[1]->VertexShader = "VertexShader.cso";

	_entities.PositionComponents[1] = new PositionComponent();
	_entities.PositionComponents[1]->Pitch = 0;
	_entities.PositionComponents[1]->Roll = 0;
	_entities.PositionComponents[1]->Yaw = 0;
	_entities.PositionComponents[1]->X = 85;
	_entities.PositionComponents[1]->Y = 20;
	_entities.PositionComponents[1]->Z = 85;

	_entities.LightComponents[1] = new LightComponent();
	_entities.LightComponents[1]->Color = DirectX::XMFLOAT4(1, 0, 0, 1);	
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
		_systemLight.Tick(_entities.PositionComponents[i], _entities.LightComponents[i], _graphics);		
		_systemRender.Tick(i, _entities.RenderComponents[i], _entities.PositionComponents[i], _graphics, _camera);

		int a = 0;
	}

	_graphics->EndDraw();
}
