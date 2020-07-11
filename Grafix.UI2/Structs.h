#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <vector>
#include <string>
#include <BitmapFile.h>

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

	void SetColor(float r, float g, float b, float a)
	{
		for (Vertex& v : Vertx)
		{
			v.Color = DirectX::XMFLOAT4(r, g, b, a);
		}
	}

	void SetColor(DirectX::XMFLOAT4 color)
	{
		for (Vertex& v : Vertx)
		{
			v.Color = color;
		}
	}
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

	//bool Enabled;

	DirectX::XMMATRIX GetModelToWorldMatrix()
	{
		//-- mat = S*R*T
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0, 1.0, 1.0);
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(X, Y, Z);
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(Pitch, Yaw, Roll);

		return S * R * T;		
	}
};

struct PhysicsComponent
{
	float VelX;
	float VelY;
	float VelZ;

	float AccX;
	float AccY;
	float AccZ;

	//bool Enabled;
};

struct LightComponent
{
	DirectX::XMFLOAT4 Direction;
	DirectX::XMFLOAT4 Color;
	float AttenA;
	float AttenB;
	float AttenC;	
	LightType LightType;

	//bool Enabled;
};

struct RenderComponent
{
	Mesh Mesh;
	std::string PixelShader;
	std::string VertexShader;
	D3D11_CULL_MODE CullMode;
	D3D11_FILL_MODE FillMode;
	D3D11_PRIMITIVE_TOPOLOGY Topology;

	//bool Enabled;
};

struct EntityData
{
	std::vector<PositionComponent*> PositionComponents;
	std::vector<LightComponent*> LightComponents;
	std::vector<PhysicsComponent*> PhysicsComponents;
	std::vector<RenderComponent*> RenderComponents;
};

//struct Entity
//{
//	int ID;
//	PositionComponent* Position;
//	LightComponent* Light;
//	PhysicsComponent* Physics;
//	RenderComponent* Render;
//};
