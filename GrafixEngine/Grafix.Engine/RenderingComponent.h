#pragma once
#include <d3d11.h>
#include <string>
#include "Mesh.h"

struct RenderingComponent
{
public:
	std::string PixelShaderID;
	std::string VertexShaderID;
	D3D11_CULL_MODE CullMode;
	D3D11_FILL_MODE FillMode;
	Mesh* Mesh;
};
