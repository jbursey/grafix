#include "RenderSystem.h"



RenderSystem::RenderSystem()
{
}


RenderSystem::~RenderSystem()
{
}

//void RenderSystem::Init(AssetSystem* assetSystem)
//{
//	_assets = assetSystem;
//}

void RenderSystem::Tick(int entityId, RenderComponent rc, PositionComponent pc, Graphics graphics, Camera camera)
{
	if (!rc.Enabled)
	{
		return;
	}

	if (!pc.Enabled)
	{
		return;
	}

	//--
	ID3D11Buffer* vbuffer = 0;
	ID3D11Buffer* ibuffer = 0;
	ID3D11Buffer* cbuffer = 0;
	ID3D11RasterizerState* rstate = 0;
	GetEntityRenderObjects(entityId, &vbuffer, &ibuffer, &cbuffer, &rstate);

	if (!vbuffer)
	{
		// create vertex buffer
		D3D11_BUFFER_DESC vertxBufferDesc;
		vertxBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		vertxBufferDesc.ByteWidth = sizeof(Vertex) * rc.Mesh.Vertx.size();
		vertxBufferDesc.CPUAccessFlags = 0;
		vertxBufferDesc.MiscFlags = 0;
		vertxBufferDesc.StructureByteStride = 0;
		vertxBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA vertexData;
		vertexData.pSysMem = &rc.Mesh.Vertx[0];
		vertexData.SysMemPitch = 0;
		vertexData.SysMemSlicePitch = 0;

		auto vbufferResult = graphics.Device->CreateBuffer(&vertxBufferDesc, &vertexData, &vbuffer);
		_entityVBuffers.insert_or_assign(entityId, vbuffer);
	}

	if (!ibuffer)
	{
		// create index buffer
		D3D11_BUFFER_DESC indexBufferDesc;
		indexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.ByteWidth = sizeof(unsigned int) * rc.Mesh.Indx.size();
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.MiscFlags = 0;
		indexBufferDesc.StructureByteStride = 0;
		indexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA indexData;
		indexData.pSysMem = &rc.Mesh.Indx[0];
		indexData.SysMemPitch = 0;
		indexData.SysMemSlicePitch = 0;

		auto ibufferResult = graphics.Device->CreateBuffer(&indexBufferDesc, &indexData, &ibuffer);
		_entityIBuffers.insert_or_assign(entityId, ibuffer);
	}

	if (!cbuffer)
	{
		//--constant buffer
		D3D11_BUFFER_DESC constantBufferDesc;
		constantBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.ByteWidth = sizeof(CBPerEntity);
		constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		constantBufferDesc.MiscFlags = 0;
		constantBufferDesc.StructureByteStride = 0;
		constantBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

		auto cbufferResult = graphics.Device->CreateBuffer(&constantBufferDesc, 0, &cbuffer);
		_entityCBuffers.insert_or_assign(entityId, cbuffer);
	}

	if (!rstate)
	{
		//--rast result
		D3D11_RASTERIZER_DESC rastDesc;
		rastDesc.AntialiasedLineEnable = true;
		rastDesc.CullMode = rc.CullMode;
		rastDesc.DepthBias = 0;
		rastDesc.DepthBiasClamp = 0.0;
		rastDesc.DepthClipEnable = false;
		rastDesc.FillMode = rc.FillMode;
		rastDesc.FrontCounterClockwise = false;
		rastDesc.MultisampleEnable = false;
		rastDesc.ScissorEnable = false;
		rastDesc.SlopeScaledDepthBias = 0;

		auto rastResult = graphics.Device->CreateRasterizerState(&rastDesc, &rstate);
		_entityRastStates.insert_or_assign(entityId, rstate);
	}

	//--draw indexed	
	graphics.Context->DrawIndexed(rc.Mesh.Indx.size(), 0, 0);

	auto modelMat = pc.GetModelToWorldMatrix();
	auto worldToCamera = camera.GetCameraMatrix();
	auto cameraToProjection = camera.GetProjectionMatrix();
	D3D11_MAPPED_SUBRESOURCE cbPerEntityResource;
	graphics.Context->Map(cbuffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &cbPerEntityResource);
	CBPerEntity* mwp = (CBPerEntity*)cbPerEntityResource.pData;
	mwp->ModelToWorld = DirectX::XMMatrixTranspose(modelMat);
	mwp->WorldToCamera = DirectX::XMMatrixTranspose(worldToCamera);
	mwp->CameraToProjection = DirectX::XMMatrixTranspose(cameraToProjection);
	graphics.Context->Unmap(cbuffer, 0);

	graphics.Context->IASetPrimitiveTopology(rc.Topology);
	graphics.Context->RSSetState(rstate);
	unsigned int strides = sizeof(Vertex);
	unsigned int offset = 0;
	graphics.Context->IASetVertexBuffers(0, 1, &vbuffer, &strides, &offset);
	graphics.Context->IASetIndexBuffer(ibuffer, DXGI_FORMAT::DXGI_FORMAT_R32_UINT, 0);
	graphics.Context->VSSetConstantBuffers(0, 1, &cbuffer);

	if (rc.Topology != D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST)
	{
		graphics.Context->DrawIndexed(rc.Mesh.Indx.size(), 0, 0);
	}
	else if (rc.Topology == D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST)
	{
		graphics.Context->Draw(rc.Mesh.Vertx.size(), 0);
	}
}

void RenderSystem::GetEntityRenderObjects(int id, ID3D11Buffer** vbuffer, ID3D11Buffer** ibuffer, ID3D11Buffer** cbuffer, ID3D11RasterizerState** rastState)
{
	if (_entityVBuffers.count(id) > 0)
	{
		ID3D11Buffer* vbufferTemp = _entityVBuffers[id];
		vbuffer = &vbufferTemp;
	}

	if (_entityIBuffers.count(id) > 0)
	{
		ID3D11Buffer* ibufferTemp = _entityIBuffers[id];
		ibuffer = &ibufferTemp;
	}

	if (_entityCBuffers.count(id) > 0)
	{
		ID3D11Buffer* cbufferTemp = _entityCBuffers[id];
		cbuffer = &cbufferTemp;
	}

	if (_entityRastStates.count(id) > 0)
	{
		ID3D11RasterizerState* rastTemp = _entityRastStates[id];
		rastState = &rastTemp;
	}
}

