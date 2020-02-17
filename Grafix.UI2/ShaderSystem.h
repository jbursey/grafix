#pragma once
#include <d3d11.h>
#include "Graphics.h"
#include "AssetSystem.h"
#include "Structs.h"

class ShaderSystem
{
public:
	ShaderSystem();
	~ShaderSystem();
	void Init(AssetSystem* assets);
	void Tick(RenderComponent rc, Graphics graphics);

private: 
	AssetSystem* _assets;
	std::map<std::string, ID3D11PixelShader*> _pixelShaders;
	std::map<std::string, ID3D11VertexShader*> _vertexShaders;
	std::map<std::string, ID3D11InputLayout*> _inputLayouts;

	void GetShaderResources(std::string pixelKey, std::string vertexKey, ID3D11PixelShader** ps, ID3D11VertexShader** vs, ID3D11InputLayout** il);
};

