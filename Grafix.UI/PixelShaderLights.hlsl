#include "Structs.hlsli"

float4 CalculateAmbientLight()
{
	return float4(0.1, 0.1, 0.1, 1); // no ambient light
	//return float4(0, 0, 0, 1);
}

float4 CalculateDirectionalDiffuseLight(float4 lightColor, float4 lightDirection, float4 inputNormal)
{
	float4 color = float4(0, 0, 0, 1);
	lightDirection = -lightDirection;
	
	float diffuseIntensity = dot(inputNormal, lightDirection);

	color = lightColor * diffuseIntensity;

	return saturate(color);
}

float4 CalculateSpotDiffuseLight(float4 lightColor, float4 lightPosition, float4 inputNormal, float4 inputWorldPosition, float falloff)
{
	float4 directionToLight = inputWorldPosition - lightPosition;
	directionToLight.w = 0; //make this a vector

	float initiaIntensity = dot(inputNormal, directionToLight);
	float4 delta = inputWorldPosition - lightPosition;
	float temp = dot(delta, delta);
	float distance = sqrt(temp);

	float intensity = 1 / pow(2.71828, falloff * distance);

	float4 color = lightColor * intensity;

	return saturate(color);
}

//-------------------------------------------------------
// main
//-------------------------------------------------------
float4 main(VertexOutput input) : SV_TARGET
{
	float4 color = input.Color;	

	float4 ambientColor = CalculateAmbientLight();

	float4 diffuseColor = CalculateDirectionalDiffuseLight(float4(1, 1, 1, 1), float4(0, -1, 0, 0), input.Normal);	

	float4 spotDiffuseColor1 = CalculateSpotDiffuseLight(float4(0, 0, 1, 1), float4(200, 10, 10, 1), input.Normal, input.PositionWorld, 0.075);
	float4 spotDiffuseColor2 = CalculateSpotDiffuseLight(float4(0, 1, 0, 1), float4(10, 10, 200, 1), input.Normal, input.PositionWorld, 0.075);
	float4 spotDiffuseColor3 = CalculateSpotDiffuseLight(float4(1, 0, 0, 1), float4(200, 10, 200, 1), input.Normal, input.PositionWorld, 0.075);

	//return color * (ambientColor);	
	//return color * (diffuseColor + ambientColor);
	//return color * (diffuseColor + ambientColor + spotDiffuseColor1);
	//return color * (diffuseColor + ambientColor + spotDiffuseColor1 + spotDiffuseColor2);
	return color * (diffuseColor + ambientColor + spotDiffuseColor1 + spotDiffuseColor2 + spotDiffuseColor3);
}