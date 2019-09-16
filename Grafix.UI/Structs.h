#pragma once
#include <DirectXMath.h>

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