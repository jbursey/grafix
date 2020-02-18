#include "Structs.hlsli"

float4 CalculateAmbientLight()
{
	//return float4(0.1, 0.1, 0.1, 1); // no ambient light
	return float4(0, 0, 0, 1);
}

float4 CalculateDirectionalDiffuseLight(float4 lightColor, float4 lightDirection, float4 inputNormal)
{
	float4 color = float4(0, 0, 0, 1);
	lightDirection = -lightDirection;

	float diffuseIntensity = dot(inputNormal, lightDirection);

	color = lightColor * diffuseIntensity;

	return saturate(color);
}

float4 CalculateSpotDiffuseLight(float4 lightColor, float4 lightPosition, float4 inputNormal, float4 inputWorldPosition, float intensityConstant, float intensityLinear, float intensitySquared)
{
	float4 directionToLight = lightPosition - inputWorldPosition;
	directionToLight.w = 0; //make this a vector

	float initialIntensity = dot(inputNormal, directionToLight);
	float4 delta = inputWorldPosition - lightPosition;
	float temp = dot(delta, delta);
	float distance = sqrt(temp);

	//float intensity = 1 / pow(2.71828, falloff * distance);
	float intensity = 1 / (intensityConstant + (intensityLinear * distance) + (intensitySquared * distance * distance));

	float4 color = lightColor * intensity * initialIntensity;

	//return float4(distance, distance, distance, 1);
	return saturate(color);
}

//-------------------------------------------------------
// main
//-------------------------------------------------------
float4 main(VertexOutput input) : SV_TARGET
{
	float4 color = input.Color;

	float4 ambientColor = CalculateAmbientLight();

	float4 diffuseColor = CalculateDirectionalDiffuseLight(float4(1, 1, 1, 1), float4(1, 0, 0, 0), input.Normal);
	//diffuseColor = float4(0, 0, 0, 1);

	float4 spotDiffuseColor = float4(0, 0, 0, 1);
	for (int i = 0; i < 20; i++)
	{
		//spotDiffuseColor += CalculateSpotDiffuseLight(pointLightPositions[i], pointLightColors[i], input.Normal, input.PositionWorld, 0.075);
		spotDiffuseColor += CalculateSpotDiffuseLight(pointLightColors[i], pointLightPositions[i], input.Normal, input.PositionWorld, 1, 0.2, 0.5);
	}

	/*float4 spotDiffuseColor1 = CalculateSpotDiffuseLight(float4(0, 0, 1, 1), float4(200, 125, 10, 1), input.Normal, input.PositionWorld, 0.075);
	float4 spotDiffuseColor2 = CalculateSpotDiffuseLight(float4(0, 1, 0, 1), float4(10, 100, 200, 1), input.Normal, input.PositionWorld, 0.075);
	float4 spotDiffuseColor3 = CalculateSpotDiffuseLight(float4(1, 0, 0, 1), float4(200, 150, 200, 1), input.Normal, input.PositionWorld, 0.075);
	float4 spotDiffuseColor4 = CalculateSpotDiffuseLight(float4(1, 0, 1, 1), float4(0, 200, 0, 1), input.Normal, input.PositionWorld, 0.075);*/

	//return color * (ambientColor);	
	//return color * (diffuseColor + ambientColor);
	//return color * (diffuseColor + ambientColor + spotDiffuseColor1);
	//return color * (diffuseColor + ambientColor + spotDiffuseColor1 + spotDiffuseColor2);
	//return color * (diffuseColor + ambientColor + spotDiffuseColor1 + spotDiffuseColor2 + spotDiffuseColor3);
	//spotDiffuseColor = CalculateSpotDiffuseLight(float4(1, 0, 0, 1), float4(0, 0, 0, 1), input.Normal, input.PositionWorld, 0.075);
	return color * (diffuseColor + ambientColor + spotDiffuseColor);
}