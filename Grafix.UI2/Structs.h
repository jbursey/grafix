#pragma once
#include <DirectXMath.h>
#include <vector>

struct Vertex
{
public:
	Vertex() : Point(0, 0, 0, 1), Color(1, 1, 1, 1), Normal(0, 0, 0, 0)
	{

	}
	DirectX::XMFLOAT4 Point;
	DirectX::XMFLOAT4 Color;
	DirectX::XMFLOAT4 Normal;
};

struct MWP
{
	DirectX::XMMATRIX ModelToWorld;
	DirectX::XMMATRIX WorldToCamera;
	DirectX::XMMATRIX CameraToProjection;
};

struct Mesh
{
	std::vector<Vertex> Vertx;
	std::vector<unsigned int> Indx;
};

struct CBPerFrame
{
	DirectX::XMFLOAT4 pointLightPositions[20];
	DirectX::XMFLOAT4 pointLightColors[20];
};
