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
	_camera.Init(width, height, 1, 1000);
	_camera.SetPosition(0, 0, 0);
	_camera.SetOrientation(0, 0, 0);

	auto m1 = MeshUtil::GetTriangle();
	Entity e1;
	e1.Init(m1, device);
	e1.SetPosition(0, 0, 10);
	e1.SetOrientation(90 * (DirectX::XM_PI / 180.0), 0, 0);
	AddEntity(e1);	
}

void Scene::Render(ID3D11DeviceContext* context)
{
	for (int i = 0; i < Entities.size(); i++)
	{
		Entity& entity = Entities[i];

		DirectX::XMMATRIX worldToCamera = _camera.GetCameraMatrix();
		DirectX::XMMATRIX cameraToProjection = _camera.GetProjectionMatrix();

		entity.Render(context, worldToCamera, cameraToProjection);
	}
}
