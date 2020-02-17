#include "Structs.hlsli"

VertexOutput main(VertexInput input)
{
	VertexOutput output;
	output.Position = mul(input.Position, ModelToWorld);
	output.Position = mul(output.Position, WorldToCamera);
	output.Position = mul(output.Position, CameraToProjection);
	output.Color = input.Color;
	//output.Normal = mul(input.Normal, ModelToWorld); //move the normal to where the object is in world space
	output.Normal = input.Normal;
	output.PositionWorld = mul(input.Position, ModelToWorld);
	return output;
}