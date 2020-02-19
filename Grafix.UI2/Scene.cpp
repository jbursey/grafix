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
	_systemAsset = new AssetSystem();
	_systemAsset->Init();
	_systemShader.Init(_systemAsset);
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
	_entities.RenderComponents[0]->Mesh = MeshUtil::GetGrid(_systemAsset->GetAsset("usgs_colo_springs.bmp"), 1.0 / 1.0);
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
	_entities.PositionComponents[1]->Y = 220;
	_entities.PositionComponents[1]->Z = 85;

	_entities.LightComponents[1] = new LightComponent();
	_entities.LightComponents[1]->Color = DirectX::XMFLOAT4(1, 0, 0, 1);	

	srand(time(0));
	for (int i = 2; i < GrafixConstants::NumLights; i++)
	{
		int x = (int)(rand() % 1081);
		int z = (int)(rand() % 1081);
		int y = (int)(rand() % 150 + 50);
		auto color = Util::CreateRandomColor();

		_entities.RenderComponents[i] = new RenderComponent();
		_entities.RenderComponents[i]->CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		_entities.RenderComponents[i]->FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		_entities.RenderComponents[i]->Mesh = MeshUtil::GetSphere(3.0, 10, 10);		
		_entities.RenderComponents[i]->Mesh.SetColor(color);
		_entities.RenderComponents[i]->PixelShader = "PixelShader.cso";
		_entities.RenderComponents[i]->Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		_entities.RenderComponents[i]->VertexShader = "VertexShader.cso";

		_entities.PositionComponents[i] = new PositionComponent();
		_entities.PositionComponents[i]->Pitch = 0;
		_entities.PositionComponents[i]->Roll = 0;
		_entities.PositionComponents[i]->Yaw = 0;
		_entities.PositionComponents[i]->X = x;
		_entities.PositionComponents[i]->Y = y;
		_entities.PositionComponents[i]->Z = z;

		_entities.LightComponents[i] = new LightComponent();		
		_entities.LightComponents[i]->Color = color;
	}

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

	for (int i = 0; i < GrafixConstants::MaxEntities; i++)
	{		
		_systemLight.Update(i, _entities.PositionComponents[i], _entities.LightComponents[i], _graphics);		

		int a = 0;
	}
}

void Scene::Tick()
{
	_graphics->BeginDraw();	

	_systemLight.Tick(_graphics);

	for (int i = 0; i < GrafixConstants::MaxEntities; i++)
	{
		_systemShader.Tick(_entities.RenderComponents[i], _graphics);		
		_systemRender.Tick(i, _entities.RenderComponents[i], _entities.PositionComponents[i], _graphics, _camera);

		int a = 0;
	}

	_graphics->EndDraw();
}
