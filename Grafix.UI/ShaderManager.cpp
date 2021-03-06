#include "ShaderManager.h"

void ShaderManager::Init(ID3D11Device* device)
{		
	_didRender = false;
	//addssstd::vector<unsigned char> pso = FileReader::ReadAllBytes("..\\x64\\Debug\\PixelShaderLights.cso");
	std::vector<unsigned char> pso = FileReader::ReadAllBytes("..\\x64\\Debug\\PixelShader.cso");
	//std::vector<unsigned char> vso = FileReader::ReadAllBytes("..\\x64\\Debug\\VertexShaderLights.cso");
	std::vector<unsigned char> vso = FileReader::ReadAllBytes("..\\x64\\Debug\\VertexShader.cso");

	auto psoResult = device->CreatePixelShader(&pso[0], pso.size(), 0, &_ps);
	auto vsoResult = device->CreateVertexShader(&vso[0], vso.size(), 0, &_vs);

	D3D11_INPUT_ELEMENT_DESC inputDesc[3];
	inputDesc[0].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	inputDesc[0].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputDesc[0].InputSlot = 0;
	inputDesc[0].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	inputDesc[0].InstanceDataStepRate = 0;
	inputDesc[0].SemanticIndex = 0;
	inputDesc[0].SemanticName = "POSITION";

	inputDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	inputDesc[1].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputDesc[1].InputSlot = 0;
	inputDesc[1].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	inputDesc[1].InstanceDataStepRate = 0;
	inputDesc[1].SemanticIndex = 0;
	inputDesc[1].SemanticName = "COLOR";

	inputDesc[2].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	inputDesc[2].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
	inputDesc[2].InputSlot = 0;
	inputDesc[2].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
	inputDesc[2].InstanceDataStepRate = 0;
	inputDesc[2].SemanticIndex = 0;
	inputDesc[2].SemanticName = "NORMAL";

	auto inputLayoutResult = device->CreateInputLayout(inputDesc, 3, &vso[0], vso.size(), &_inputLayout);

	int stop = 0;
}

void ShaderManager::Render(ID3D11DeviceContext* context)
{
	if (!_didRender)
	{
		context->IASetInputLayout(_inputLayout);
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		context->PSSetShader(_ps, 0, 0);
		context->VSSetShader(_vs, 0, 0);		

		_didRender = true;
	}	
}
