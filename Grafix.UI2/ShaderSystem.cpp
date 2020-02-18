#include "ShaderSystem.h"

ShaderSystem::ShaderSystem()
{
}

ShaderSystem::~ShaderSystem()
{
}

void ShaderSystem::Init(AssetSystem* assets)
{
	_assets = assets;
}

void ShaderSystem::Tick(RenderComponent* rc, Graphics* graphics)
{
	if (!rc)
	{
		return;
	}

	ID3D11PixelShader* ps = 0;
	ID3D11VertexShader* vs = 0;
	ID3D11InputLayout* il = 0;

	GetShaderResources(rc->PixelShader, rc->VertexShader, &ps, &vs, &il);

	if (!ps)
	{
		std::vector<unsigned char> psBytes = _assets->GetAsset(rc->PixelShader);
		auto psoResult = graphics->Device->CreatePixelShader(&psBytes[0], psBytes.size(), 0, &ps);
		_pixelShaders.insert_or_assign(rc->PixelShader, ps);
	}

	if (!vs)
	{
		std::vector<unsigned char> vsBytes = _assets->GetAsset(rc->VertexShader);
		auto psoResult = graphics->Device->CreateVertexShader(&vsBytes[0], vsBytes.size(), 0, &vs);
		_vertexShaders.insert_or_assign(rc->VertexShader, vs);

		//--make better ugh
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

		auto inputLayoutResult = graphics->Device->CreateInputLayout(inputDesc, 3, &vsBytes[0], vsBytes.size(), &il);
		_inputLayouts.insert_or_assign(rc->VertexShader, il);
	}

	if (!il)
	{
		//see above. Make this better.
	}

	if (_lastInputLayout != rc->VertexShader)
	{
		graphics->Context->IASetInputLayout(il);
		_lastInputLayout = rc->VertexShader;
	}
	if (_lastPixelShader != rc->PixelShader)
	{
		graphics->Context->PSSetShader(ps, 0, 0);
		_lastPixelShader = rc->PixelShader;
	}
	if (_lastVertexShader != rc->VertexShader)
	{
		graphics->Context->VSSetShader(vs, 0, 0);
		_lastVertexShader = rc->VertexShader;
	}

}

void ShaderSystem::GetShaderResources(std::string pixelKey, std::string vertexKey, ID3D11PixelShader** ps, ID3D11VertexShader** vs, ID3D11InputLayout** il)
{
	
	if (_pixelShaders.count(pixelKey) > 0)
	{
		ID3D11PixelShader* temp = _pixelShaders[pixelKey];
		*ps = temp;
	}

	if (_vertexShaders.count(vertexKey) > 0)
	{
		ID3D11VertexShader* temp = _vertexShaders[vertexKey];
		*vs = temp;
	}

	if (_inputLayouts.count(vertexKey) > 0)
	{
		ID3D11InputLayout* temp = _inputLayouts[vertexKey];
		*il = temp;
	}
}
