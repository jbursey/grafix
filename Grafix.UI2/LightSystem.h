#pragma once
#include <map>
#include "Graphics.h"
#include "Structs.h"
#include "GrafixConstants.h"
#include "Util.h"

class LightSystem
{
public:
	LightSystem();
	~LightSystem();
	void Init(Graphics* graphics);
	void Update(int entityId, PositionComponent* pc, LightComponent* lc, Graphics* graphics);
	void Tick(Graphics* graphics);

private:
	ID3D11Buffer* _buffer;
	//int _currentLightIndex;
	//CBPerFrame _cbPerFrame;

	struct LightPoint
	{
		DirectX::XMFLOAT4 Position;
		DirectX::XMFLOAT4 Color;
	};

	std::map<int, LightPoint> _lightPointsThisFrame;
	//std::vector<LightPoint> _lightPointsThisFrame;

};

