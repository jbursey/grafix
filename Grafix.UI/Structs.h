#pragma once
#include <DirectXMath.h>
#include <vector>

struct Vertex
{
	DirectX::XMFLOAT4 Point;
	DirectX::XMFLOAT4 Color;
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