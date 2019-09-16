#pragma once
#include <d3d11.h>
#include <vector>
#include "Structs.h"
#include <DirectXMath.h>

class TriangleTest
{
public:	
	void Init(ID3D11Device* device);
	void Update();
	void Render(ID3D11DeviceContext* context);
	DirectX::XMFLOAT4X4 ModelToWorld;

private:
	std::vector<Vertex> _vertx;
	std::vector<unsigned int> _indx;
	ID3D11Buffer* _vbuffer;
	ID3D11Buffer* _ibuffer;
	ID3D11Buffer* _cbuffer;	
	MWP _mwp;
};

