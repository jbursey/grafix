#pragma once
#include <d3d11.h>
#include <FileReader.h>
#include <vector>
#include <d3d11.h>

class ShaderManager
{
public:
	void Init(ID3D11Device* device);
	void Render(ID3D11DeviceContext* context);

private:
	ID3D11PixelShader* _ps;
	ID3D11VertexShader* _vs;
	ID3D11InputLayout* _inputLayout;

	//fix later
	bool _didRender;
};

