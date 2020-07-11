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
	_camera.SetPosition(10, 0, 10);
	_camera.MoveForward();

	//--struct of arrays
	_entities.LightComponents.resize(GrafixConstants::MaxEntities);
	_entities.PositionComponents.resize(GrafixConstants::MaxEntities);
	_entities.PhysicsComponents.resize(GrafixConstants::MaxEntities);
	_entities.RenderComponents.resize(GrafixConstants::MaxEntities);

	//--turn all components off
	for (int i = 0; i < GrafixConstants::MaxEntities; i++)
	{
		_entities.LightComponents[i] = 0;
		_entities.PhysicsComponents[i] = 0;
		_entities.PositionComponents[i] = 0;
		_entities.RenderComponents[i] = 0;
	}

	//--systems init
	RenderComponent* terrainRC;
	PositionComponent* terrainPC;
	_systemTerrain = new TerrainSystem();
	_systemAsset = new AssetSystem();
	_systemAsset->Init();
	_systemTerrain->Init(_entities, MeshUtil::GetGrid(_systemAsset->GetAsset("mt_shasta.bmp"), 1.0 / 1.0));
	_systemShader.Init(_systemAsset);
	_systemLight.Init(_graphics);


	//--make some entities	
	//--move entity to terrain
	//_entities.RenderComponents[0] = new RenderComponent();
	//_entities.RenderComponents[0]->CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	//_entities.RenderComponents[0]->FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	//_entities.RenderComponents[0]->Mesh = MeshUtil::GetGrid(_systemAsset->GetAsset("usgs_colo_springs.bmp"), 1.0 / 1.0);
	//_entities.RenderComponents[0]->PixelShader = "PixelShaderLights.cso";
	//_entities.RenderComponents[0]->Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	//_entities.RenderComponents[0]->VertexShader = "VertexShaderLights.cso";
	//
	//_entities.PositionComponents[0] = new PositionComponent();
	//_entities.PositionComponents[0]->Pitch = 0;
	//_entities.PositionComponents[0]->Roll = 0;
	//_entities.PositionComponents[0]->Yaw = 0;
	//_entities.PositionComponents[0]->X = 0;
	//_entities.PositionComponents[0]->Y = 0;
	//_entities.PositionComponents[0]->Z = 0;		


	_entities.RenderComponents[2] = new RenderComponent();
	_entities.RenderComponents[2]->CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	_entities.RenderComponents[2]->FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	_entities.RenderComponents[2]->Mesh = MeshUtil::GetSphere(5.0, 30, 30);	
	_entities.RenderComponents[2]->Mesh.SetColor(1, 0, 0, 1);
	_entities.RenderComponents[2]->PixelShader = "PixelShader.cso";
	_entities.RenderComponents[2]->Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	_entities.RenderComponents[2]->VertexShader = "VertexShader.cso";

	_entities.PositionComponents[2] = new PositionComponent();
	_entities.PositionComponents[2]->Pitch = 0;
	_entities.PositionComponents[2]->Roll = 0;
	_entities.PositionComponents[2]->Yaw = 0;
	_entities.PositionComponents[2]->X = 0;
	_entities.PositionComponents[2]->Y = 0;
	_entities.PositionComponents[2]->Z = 0;

	_entities.LightComponents[2] = new LightComponent();
	_entities.LightComponents[2]->Color = DirectX::XMFLOAT4(1, 0, 0, 1);	

	srand(time(0));	
	for (int i = 3; i < GrafixConstants::NumLights + 3; i++)	
	{
		int x = (int)(rand() % 1081);
		int z = (int)(rand() % 1081);
		int y = (int)(rand() % 150 + 50);	
		//y = 0;

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

	//PositionComponent* cameraPC = new PositionComponent();
	//DirectX::XMFLOAT3 pos = _camera.GetPosition();
	//cameraPC->X = -pos.x;
	//cameraPC->Y = pos.y;
	//cameraPC->Z = -pos.z;
	//_systemTerrain->Update(cameraPC, true, false);
	//_camera.SetPosition(pos.x, -cameraPC->Y - 4, pos.z);
	//delete cameraPC;

	for (int i = 0; i < GrafixConstants::MaxEntities; i++)
	{
		if (i == GrafixConstants::EntityTerrainID)
		{
			continue;
		}

		_systemTerrain->Update(_entities.PositionComponents[i], false, false);		
	}
	

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
