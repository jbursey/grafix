#pragma once
#include <DirectXMath.h>
#include <vector>
#include <d3d11.h>
#include "Structs.h"

class Entity
{
public:
	Entity();
	~Entity();
	
	void Init(Mesh mesh, ID3D11Device* device);
	void Render(ID3D11DeviceContext* context, DirectX::XMMATRIX worldToCamera, DirectX::XMMATRIX cameraToProjection);
	void SetPosition(float x, float y, float z);
	void SetOrientation(float roll, float pitch, float yaw);
	void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
	D3D11_CULL_MODE Cull;
	D3D11_FILL_MODE Fill;
	DirectX::XMMATRIX GetModelToWorldMatrix();

	Mesh GetMesh();
private:
	float _x;
	float _y;
	float _z;

	float _roll;
	float _pitch;
	float _yaw;

	Mesh _mesh;
	//std::vector<Vertex> _vertx;
	//std::vector<unsigned int> _indx;
	ID3D11RasterizerState* _rasterizerState;

	ID3D11Buffer* _vbuffer;
	ID3D11Buffer* _ibuffer;
	ID3D11Buffer* _cbuffer;

	D3D11_PRIMITIVE_TOPOLOGY _topology;
};

