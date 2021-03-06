#include "Structs.hlsli"

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	//output.Position = input.Position;
	output.Position = mul(input.Position, ModelToWorld);
	output.Position = mul(output.Position, WorldToCamera);
	output.Position = mul(output.Position, CameraToProjection);
	//output.Position = input.Position;
	output.Color = input.Color;
	output.Normal = mul(input.Normal, ModelToWorld);
	output.PositionWorld = mul(input.Position, ModelToWorld);
	return output;
}