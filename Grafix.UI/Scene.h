#pragma once
#include "Entity.h"
#include "Camera.h"
#include <d3d11.h>
#include <vector>
#include "MeshUtil.h"

class Scene
{
public:
	Scene();
	~Scene();
	std::vector<Entity> Entities;
	void AddEntity(Entity entity);
	void Init(int width, int height, ID3D11Device* device);
	void Render(ID3D11DeviceContext* context);

private:
	Camera _camera;
};

