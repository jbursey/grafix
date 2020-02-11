#pragma once
#include <vector>
#include <d3d11.h>
#include "Structs.h"
#include "GrafixConstants.h"
#include "Util.h"

class LightSystem
{
public:
	LightSystem();
	void Init(ID3D11Device* device);
	void Update();
	void Render(ID3D11DeviceContext* context);
	CBPerFrame Lights;

private:	
	//CBPerFrame _cbPerFrame;
	ID3D11Buffer* _buffer;
};

