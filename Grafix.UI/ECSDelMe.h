#pragma once
#include "Structs.h"
#include <d3d11.h>
#include <vector>

struct PositionComponent
{
public:
	PositionComponent() : X(0), Y(0), Z(0) {}
	float X;
	float Y;
	float Z;
};

struct OrientationComponent
{
public:
	OrientationComponent() : Pitch(0), Yaw(0), Roll(0) {}
	float Pitch;
	float Yaw;
	float Roll;
};

struct ScalingComponent
{
public:
	ScalingComponent() : X(0), Y(0), Z(0) {}
	float X;
	float Y;
	float Z;
};

struct MeshComponent
{
public:
	MeshComponent() {}
	std::vector<Vertex> Vertx;
	std::vector<unsigned int> Indx;
};

struct RenderingComponent
{
public:
	RenderingComponent() : Topology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST), CullMode(D3D11_CULL_MODE::D3D11_CULL_NONE), FillMode(D3D11_FILL_MODE::D3D11_FILL_WIREFRAME)
	{

	}
	D3D11_PRIMITIVE_TOPOLOGY Topology;
	D3D11_CULL_MODE CullMode;
	D3D11_FILL_MODE FillMode;
};

struct Entity
{
public:
	int ID;
	PositionComponent PositionComponent;
	OrientationComponent OrientationComponent;
	ScalingComponent ScalingComponent;
	MeshComponent MeshComponent;
	
};