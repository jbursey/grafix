struct VertexInput
{
	float4 Position : POSITION; 
	float4 Color : COLOR;
};

struct VertexOutput
{
	float4 Position : SV_POSITION;
	float4 Color : COLOR;
};

//struct PixelInput
//{
//	float4 Position : POSITION;
//	float4 Color : COLOR;
//};