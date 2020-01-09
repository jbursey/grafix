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

	//--at origin
	auto sphere = MeshUtil::GetSphere(3, 10, 10);
	Entity e5;
	e5.Init(sphere, device);
	e5.SetPosition(0, 0, 0);
	e5.SetOrientation(0, 0, 0);	
	e5.SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	AddEntity(e5);

	auto sphere2 = MeshUtil::GetSphere(3, 10, 10);
	Entity e6;
	e6.Init(sphere2, device);
	e6.SetPosition(0, 0, 0);
	e6.SetOrientation(0, 0, 0);
	e6.SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);	
	AddEntity(e6);
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
