#include "Structs.hlsli"

float4 main(VertexOutput input) : SV_TARGET
{
	float4 color = input.Color;

	//--hard code a directional light
	float4 lightColor = float4(1, 1, 1, 1);
	float4 lightDirection = float4(0, -1, 0, 0);
	lightDirection = -lightDirection;

	float4 ambientColor = float4(0, 0, 0, 1);
	float4 diffuseColor = float4(1, 1, 1, 1);
	float intensity = dot(input.Normal, lightDirection);
	//intensity = 1.0;
	//float4 finalColor = color + ambientColor + (diffuseColor * intensity);
	float4 finalColor = diffuseColor * intensity;
	
	return finalColor;
}