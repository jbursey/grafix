#include "Entity.h"



Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::Init(Mesh mesh, ID3D11Device* device)
{
	_mesh = mesh;
	_topology = D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	// create vertex buffer
	D3D11_BUFFER_DESC vertxBufferDesc;
	vertxBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	vertxBufferDesc.ByteWidth = sizeof(Vertex) * mesh.Vertx.size();
	vertxBufferDesc.CPUAccessFlags = 0;
	vertxBufferDesc.MiscFlags = 0;
	vertxBufferDesc.StructureByteStride = 0;
	vertxBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA vertexData;
	vertexData.pSysMem = &mesh.Vertx[0];
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	auto vbufferResult = device->CreateBuffer(&vertxBufferDesc, &vertexData, &_vbuffer);

	// create index buffer
	D3D11_BUFFER_DESC indexBufferDesc;
	indexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.ByteWidth = sizeof(unsigned int) * mesh.Indx.size();
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA indexData;
	indexData.pSysMem = &mesh.Indx[0];
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

	//--rast result
	D3D11_RASTERIZER_DESC rastDesc;
	rastDesc.AntialiasedLineEnable = true;
	rastDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	rastDesc.DepthBias = 0;
	rastDesc.DepthBiasClamp = 1.0;
	rastDesc.DepthClipEnable = false;
	rastDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	rastDesc.FrontCounterClockwise = false;
	rastDesc.MultisampleEnable = false;
	rastDesc.ScissorEnable = false;
	rastDesc.SlopeScaledDepthBias = 0;

	auto rastResult = device->CreateRasterizerState(&rastDesc, &_rasterizerState);
}

void Entity::Render(ID3D11DeviceContext* context, DirectX::XMMATRIX worldToCamera, DirectX::XMMATRIX cameraToProjection)
{
	auto modelMat = GetModelToWorldMatrix();
	D3D11_MAPPED_SUBRESOURCE cbMVP;
	context->Map(_cbuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &cbMVP);
	MWP* mwp = (MWP*)cbMVP.pData;
	mwp->ModelToWorld = DirectX::XMMatrixTranspose(modelMat);
	mwp->WorldToCamera = DirectX::XMMatrixTranspose(worldToCamera);
	mwp->CameraToProjection = DirectX::XMMatrixTranspose(cameraToProjection);
	context->Unmap(_cbuffer, 0);

	context->IASetPrimitiveTopology(_topology);
	context->RSSetState(_rasterizerState);
	unsigned int strides = sizeof(Vertex);
	unsigned int offset = 0;
	context->IASetVertexBuffers(0, 1, &_vbuffer, &strides, &offset);
	context->IASetIndexBuffer(_ibuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	context->VSSetConstantBuffers(0, 1, &_cbuffer);

	if (_topology == D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
	{
		context->DrawIndexed(_mesh.Indx.size(), 0, 0);
	}
	else if (_topology == D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST)
	{
		context->Draw(_mesh.Vertx.size(), 0);
	}
	
}

void Entity::SetPosition(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Entity::SetOrientation(float roll, float pitch, float yaw)
{
	_roll = roll;
	_pitch = pitch;
	_yaw = yaw;
}

void Entity::SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	_topology = topology;
}

DirectX::XMMATRIX Entity::GetModelToWorldMatrix()
{
	//-- mat = S*R*T
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0, 1.0, 1.0);
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(_x, _y, _z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(_pitch, _yaw, _roll);

	return S*R*T;
	//return T*R*S;
}
