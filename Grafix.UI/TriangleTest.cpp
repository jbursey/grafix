#include "TriangleTest.h"

void TriangleTest::Init(ID3D11Device* device)
{
	Vertex v1;
	Vertex v2;
	Vertex v3;

	v1.Point = DirectX::XMFLOAT4(-1, -1, 0, 1); //1 in the w component for POSITIONS and a 0 for VECTORS
	v1.Color = DirectX::XMFLOAT4(1, 0, 0, 1);

	v2.Point = DirectX::XMFLOAT4(0, 1, 0, 1); //1 in the w component for POSITIONS and a 0 for VECTORS
	v2.Color = DirectX::XMFLOAT4(0, 1, 0, 1);

	v3.Point = DirectX::XMFLOAT4(1, -1, 0, 1); //1 in the w component for POSITIONS and a 0 for VECTORS
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

	//--constant buffer
	D3D11_BUFFER_DESC constantBufferDesc;
	constantBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.ByteWidth = sizeof(MWP);
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;
	constantBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

	auto cbufferResult = device->CreateBuffer(&constantBufferDesc, 0, &_cbuffer);

	//--model to world default
	DirectX::XMMATRIX translationMatrix = DirectX::XMMatrixTranslation(0, 0, 10);
	DirectX::XMStoreFloat4x4(&ModelToWorld, translationMatrix);		
}

void TriangleTest::Update()
{
}

void TriangleTest::Render(ID3D11DeviceContext* context)
{		
	//D3D11_MAPPED_SUBRESOURCE sub;
	//sub.pData = &_vertx[0];
	//sub.DepthPitch = 0;
	//sub.RowPitch = 0;
	//context->Map(_vbuffer, 0, D3D11_MAP::D3D11_MAP_READ_WRITE, 0, &sub);
	//_vertx[0].Color.x = (rand() % 255) / 255.0;
	//context->Unmap(_vbuffer, 0);
	auto modelToWorld = DirectX::XMMatrixTranslation(0, 0, 1.5);	
	auto worldToCamera = DirectX::XMMatrixIdentity();
	auto cameraToProjection = DirectX::XMMatrixPerspectiveFovLH(75 * (DirectX::XM_PI / 180.0), 1000 / 800.0, 1.0, 1000.0);

	

	D3D11_MAPPED_SUBRESOURCE sub;
	//sub.pData = &_mwp;
	//sub.DepthPitch = 0;
	//sub.RowPitch = 0;
	context->Map(_cbuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &sub);
	MWP* mwp = (MWP*)sub.pData;
	mwp->ModelToWorld = DirectX::XMMatrixTranspose(modelToWorld);
	mwp->WorldToCamera = DirectX::XMMatrixTranspose(worldToCamera);
	mwp->CameraToProjection = DirectX::XMMatrixTranspose(cameraToProjection);
	context->Unmap(_cbuffer, 0);

	unsigned int strides = sizeof(Vertex);
	unsigned int offset = 0;
	context->IASetVertexBuffers(0, 1, &_vbuffer, &strides, &offset);
	context->IASetIndexBuffer(_ibuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);		
	context->VSSetConstantBuffers(0, 1, &_cbuffer);
	context->DrawIndexed(_indx.size(), 0, 0);
}
