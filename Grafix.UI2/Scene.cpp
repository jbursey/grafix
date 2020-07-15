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
	int worldWidth = 100;
	int worldDepth = 100;
	RenderComponent* terrainRC;
	PositionComponent* terrainPC;
	_systemTerrain = new TerrainSystem();
	_systemAsset = new AssetSystem();
	_systemTexture = new TextureSystem();
	_systemAsset->Init();
	//_systemTerrain->Init(_entities, MeshUtil::GetGrid(_systemAsset->GetAsset("mt_shasta.bmp"), 1.0 / 1.0));
	//_systemTerrain->Init(_entities, MeshUtil::GetGrid(_systemAsset->GetAsset("perlin.bmp"), 1.0 / 1.0));
	_systemTerrain->Init(_entities, MeshUtil::GetGrid(worldWidth, worldDepth));
	_systemShader.Init(_systemAsset);
	_systemLight.Init(_graphics);	
	_systemTexture->Init(_graphics);
	


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
	_entities.RenderComponents[2]->PixelShader = "PixelShaderTexture.cso";
	_entities.RenderComponents[2]->Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	_entities.RenderComponents[2]->VertexShader = "VertexShader.cso";

	_entities.PositionComponents[2] = new PositionComponent();
	_entities.PositionComponents[2]->Pitch = 0;
	_entities.PositionComponents[2]->Roll = 0;
	_entities.PositionComponents[2]->Yaw = 0;
	_entities.PositionComponents[2]->X = 0;
	_entities.PositionComponents[2]->Y = 50;
	_entities.PositionComponents[2]->Z = 0;

	_entities.LightComponents[2] = new LightComponent();
	_entities.LightComponents[2]->Color = DirectX::XMFLOAT4(1, 0, 0, 1);	
	_entities.LightComponents[2]->AttenA = 1.0;
	_entities.LightComponents[2]->AttenB = 0.25;
	_entities.LightComponents[2]->AttenC = 0.05;

	srand(time(0));	
	for (int i = 3; i < GrafixConstants::NumLights + 3; i++)
	{
		int x = (int)(rand() % worldWidth);
		int z = (int)(rand() % worldDepth);
		int y = (int)(rand() % 250 + 25);
		//y = 0;

		if (i == 3)
		{
			x = worldWidth / 2.0;
			y = 4.0;
			z = worldDepth / 2.0;
		}

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
		_entities.LightComponents[i]->AttenA = 1.0;
		_entities.LightComponents[i]->AttenB = 0.25;
		_entities.LightComponents[i]->AttenC = 0.05;

		if (i == 3)
		{
			//_entities.LightComponents[i]->AttenB = 0.025;
			//_entities.LightComponents[i]->AttenC = 0.00000000;
		}
	}

	//RenderNormalEntityData();
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
		_systemTexture->Tick(_graphics);
		_systemShader.Tick(_entities.RenderComponents[i], _graphics);		
		_systemRender.Tick(i, _entities.RenderComponents[i], _entities.PositionComponents[i], _graphics, _camera);

		int a = 0;
	}

	_graphics->EndDraw();
}

void Scene::RenderNormalEntityData()
{
	//entity 2 = sphere...start here
	Mesh normals;

	unsigned int ixCounter = 0;
	auto color = Util::CreateRandomColor();

	for (int i = 0; i < GrafixConstants::MaxEntities; i++)
	{
		if (i == 2 || true) //remove me
		{
			if (_entities.RenderComponents[i])
			{
				for (int j = 0; j < _entities.RenderComponents[i]->Mesh.Vertx.size(); j++)
				{
					Vertex v = _entities.RenderComponents[i]->Mesh.Vertx[j];

					//need to create a line at vertex v in the direction of the normal. This will render as a line in the render system and it needs 2 vertex and 2 index;
					Vertex v1;
					Vertex v2;

					v1.Color = color;
					v1.Normal = DirectX::XMFLOAT4(0, 0, 0, 0);
					v1.Point = v.Point;

					v2.Color = color;
					v2.Normal = DirectX::XMFLOAT4(0, 0, 0, 0);
					v2.Point = DirectX::XMFLOAT4(v.Point.x + v.Normal.x, v.Point.y + v.Normal.y, v.Point.z + v.Normal.z, 1);

					v1.Point.x += _entities.PositionComponents[i]->X;
					v1.Point.y += _entities.PositionComponents[i]->Y;
					v1.Point.z += _entities.PositionComponents[i]->Z;

					v2.Point.x += _entities.PositionComponents[i]->X;
					v2.Point.y += _entities.PositionComponents[i]->Y;
					v2.Point.z += _entities.PositionComponents[i]->Z;
					

					normals.Vertx.push_back(v1);
					normals.Vertx.push_back(v2);
					normals.Indx.push_back(ixCounter++);
					normals.Indx.push_back(ixCounter++);
				}
			}
		}
	}

	_entities.RenderComponents[GrafixConstants::EntityNormals] = new RenderComponent();
	_entities.RenderComponents[GrafixConstants::EntityNormals]->CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	_entities.RenderComponents[GrafixConstants::EntityNormals]->FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	_entities.RenderComponents[GrafixConstants::EntityNormals]->Mesh = normals;
	_entities.RenderComponents[GrafixConstants::EntityNormals]->PixelShader = "PixelShader.cso";
	_entities.RenderComponents[GrafixConstants::EntityNormals]->Topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
	_entities.RenderComponents[GrafixConstants::EntityNormals]->VertexShader = "VertexShader.cso";

	_entities.PositionComponents[GrafixConstants::EntityNormals] = new PositionComponent();
	_entities.PositionComponents[GrafixConstants::EntityNormals]->Pitch = 0;
	_entities.PositionComponents[GrafixConstants::EntityNormals]->Roll = 0;
	_entities.PositionComponents[GrafixConstants::EntityNormals]->Yaw = 0;
	_entities.PositionComponents[GrafixConstants::EntityNormals]->X = 0;
	_entities.PositionComponents[GrafixConstants::EntityNormals]->Y = 0;
	_entities.PositionComponents[GrafixConstants::EntityNormals]->Z = 0;
}

