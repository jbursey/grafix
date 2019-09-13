#include "TriangleTest.h"

void TriangleTest::Init(ID3D11Device* device)
{
	Vertex v1;
	Vertex v2;
	Vertex v3;

	v1.Point = DirectX::XMFLOAT4(-1, -1, 10, 1); //1 in the w component for POSITIONS and a 0 for VECTORS
	v1.Color = DirectX::XMFLOAT4(1, 0, 0, 1);

	v2.Point = DirectX::XMFLOAT4(0, 1, 10, 1); //1 in the w component for POSITIONS and a 0 for VECTORS
	v2.Color = DirectX::XMFLOAT4(0, 1, 0, 1);

	v3.Point = DirectX::XMFLOAT4(1, -1, 10, 1); //1 in the w component for POSITIONS and a 0 for VECTORS
	v3.Color = DirectX::XMFLOAT4(0, 0, 1, 1);

	_vertx.push_back(v1);
	_vertx.push_back(v2);
	_vertx.push_back(v3);

	_indx.push_back(0);
	_indx.push_back(1);
	_indx.push_back(2);

	// create vertex buffer
	D3D11_BUFFER_DESC vertxBufferDesc;
	vertxBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	vertxBufferDesc.ByteWidth = sizeof(Vertex) * _vertx.size();
	vertxBufferDesc.CPUAccessFlags = 0;
	vertxBufferDesc.MiscFlags = 0;
	vertxBufferDesc.StructureByteStride = 0;
	vertxBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = &_vertx[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	auto vbufferResult = device->CreateBuffer(&vertxBufferDesc, &vertexData, &_vbuffer);

	// create index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * _indx.size();
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = &_indx[0];
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	auto ibufferResult = device->CreateBuffer(&indexBufferDesc, &indexData, &_ibuffer);
	int sto = 0;
}

void TriangleTest::Update()
{
}

void TriangleTest::Render(ID3D11DeviceContext* context)
{	
	unsigned int strides = sizeof(Vertex);
	unsigned int offset = 0;
	context->IASetVertexBuffers(0, 1, &_vbuffer, &strides, &offset);
	context->IASetIndexBuffer(_ibuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);	
	context->DrawIndexed(_indx.size(), 0, 0);
}
