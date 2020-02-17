#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <vector>
#include <map>
#include "Structs.h"
#include "Graphics.h"
#include "Camera.h"
//#include "AssetSystem.h"

class RenderSystem
{
public:
	RenderSystem();
	~RenderSystem();	
	//void Init(AssetSystem* assetSystem);
	void Tick(int entityId, RenderComponent rc, PositionComponent pc, Graphics graphics, Camera camera);

private:
	std::map<int, ID3D11Buffer*> _entityVBuffers;
	std::map<int, ID3D11Buffer*> _entityIBuffers;
	std::map<int, ID3D11Buffer*> _entityCBuffers;
	std::map<int, ID3D11RasterizerState*> _entityRastStates;
	void GetEntityRenderObjects(int id, ID3D11Buffer** vbuffer, ID3D11Buffer** ibuffer, ID3D11Buffer** cbuffer, ID3D11RasterizerState** rastState);
	//AssetSystem* _assets;
};

