#include "Structs.hlsli"

SamplerState _samplerState;
Texture2D _image;

float4 main(VertexOutput input) : SV_TARGET
{
	return _image.Sample(_samplerState, input.TextureUV);
}