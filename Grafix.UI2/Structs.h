#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
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

struct CBPerEntity
{
	DirectX::XMMATRIX ModelToWorld;
	DirectX::XMMATRIX WorldToCamera;
	DirectX::XMMATRIX CameraToProjection;
};

struct CBPerFrame
{
	DirectX::XMFLOAT4 pointLightPositions[20];
	DirectX::XMFLOAT4 pointLightColors[20];
};

enum LightType
{
	LIGHT_TYPE_POINT,
	LIGHT_TYPE_SPOT,
	LIGHT_TYPE_DIRECTION
};

struct Mesh
{
	std::vector<Vertex> Vertx;
	std::vector<unsigned int> Indx;
};

//-------------ECS
struct PositionComponent
{
	float X;
	float Y;
	float Z;

	float Pitch;
	float Yaw;
	float Roll;
};

struct PhysicsComponent
{
	float VelX;
	float VelY;
	float VelZ;

	float AccX;
	float AccY;
	float AccZ;
};



struct LightComponent
{
	DirectX::XMFLOAT4 Direction;
	DirectX::XMFLOAT4 Color;
	float AttenA;
	float AttenB;
	float AttenC;	
	LightType LightType;
};

struct RenderComponent
{
	Mesh Mesh;
	D3D11_CULL_MODE CullMode;
	D3D11_FILL_MODE FillMode;	
};

struct EntityData
{
	std::vector<PositionComponent> PositionComponents;
	std::vector<LightComponent> LightComponents;
	std::vector<PhysicsComponent> PhysicsComponents;
	std::vector<RenderComponent> RenderComponents;
};
