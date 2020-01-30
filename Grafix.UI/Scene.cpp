#include "Scene.h"



Scene::Scene()
{
	
}


Scene::~Scene()
{
}

void Scene::AddEntity(Entity entity)
{
	Entities.push_back(entity);
}

void Scene::Init(int width, int height, ID3D11Device* device)
{
	
	Camera.Init(width, height, 1, 1000);
	Camera.SetPosition(0, 0, 0);
	Camera.SetOrientation(0, 0, 0);

	//four triangles for reference

	////--into screen
	//auto m1 = MeshUtil::GetTriangle();
	//Entity e1;
	//e1.Init(m1, device);
	//e1.SetPosition(0, 0, 10);
	//e1.SetOrientation(0 * (DirectX::XM_PI / 180.0), 0, 0);
	//e1.SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	//AddEntity(e1);

	////--behind
	//auto m2 = MeshUtil::GetTriangle();
	//Entity e2;
	//e2.Init(m2, device);
	//e2.SetPosition(0, 0, -10);
	//e2.SetOrientation(0 * (DirectX::XM_PI / 180.0), 0, 0);
	//AddEntity(e2);

	////--to right
	//auto m3 = MeshUtil::GetTriangle();
	//Entity e3;
	//e3.Init(m3, device);
	//e3.SetPosition(10, 0, 0);
	//e3.SetOrientation(0 * (DirectX::XM_PI / 180.0), 0, 90 * (DirectX::XM_PI / 180.0));
	//AddEntity(e3);

	////--to left
	//auto m4 = MeshUtil::GetTriangle();
	//Entity e4;
	//e4.Init(m1, device);
	//e4.SetPosition(-10, 0, 0);
	//e4.SetOrientation(0 * (DirectX::XM_PI / 180.0), 0, 90 * (DirectX::XM_PI / 180.0));
	//AddEntity(e4);

	int size = 20;

	//--at origin
	auto sphere = MeshUtil::GetSphere(10, size, size);
	Entity e5;
	e5.Init(sphere, device);
	e5.SetPosition(0, 0, 0);
	e5.SetOrientation(0, 0, 0);	
	e5.SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	AddEntity(e5);

	//auto sphere2 = MeshUtil::GetSphere(10, size, size);
	Entity e6;
	e6.Init(sphere, device);
	e6.SetPosition(0, 0, 15);
	e6.SetOrientation(0, 0, 0);
	e6.SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);	
	AddEntity(e6);

	int w = 10;
	int d = 10;
	auto grid = MeshUtil::GetGrid(w, d);
	Entity e7;
	e7.Init(grid, device);
	e7.SetPosition(0, -50, 0);
	e7.SetOrientation(0, 0, 0);
	e7.SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	AddEntity(e7);

	//auto grid2 = MeshUtil::GetGrid("..\\test_bitmap.bmp", 1/128.0);
	auto grid2 = MeshUtil::GetGrid("..\\heightmap5.bmp", 1 / 10.0);
	//auto grid2 = MeshUtil::GetGrid("..\\heightmap_test.bmp", 1 / 10.0);
	Entity e8;
	e8.Init(grid2, device);
	e8.SetPosition(0, 0, 0);
	e8.SetOrientation(0, 0, 0);
	e8.SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	AddEntity(e8);
}

void Scene::Render(ID3D11DeviceContext* context)
{		
	for (int i = 0; i < Entities.size(); i++)
	{
		Entity& entity = Entities[i];

		DirectX::XMMATRIX worldToCamera = Camera.GetCameraMatrix();
		DirectX::XMMATRIX cameraToProjection = Camera.GetProjectionMatrix();

		entity.Render(context, worldToCamera, cameraToProjection);
	}
}
