struct VertexInput
{
	float4 Position : POSITION; 
	float4 Color : COLOR;
	float4 Normal : NORMAL;
};

struct VertexOutput
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
	float4 Normal : NORMAL;
	float4 PositionWorld: POSITION;
};

cbuffer cbMWP : register(b0)
{
	matrix ModelToWorld;
	matrix WorldToCamera;
	matrix CameraToProjection;
};

//struct PixelInput
//{
//	float4 Position : POSITION;
//	float4 Color : COLOR;
//};t