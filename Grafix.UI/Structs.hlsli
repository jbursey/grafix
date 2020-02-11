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

cbuffer cbPerFrame : register(b1)
{	
	float4 pointLightPositions[20];
	float4 pointLightColors[20];
}

//struct PixelInput
//{
//	float4 Position : POSITION;
//	float4 Color : COLOR;
//};t