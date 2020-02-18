#pragma once
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
	void Tick(PositionComponent* pc, LightComponent* lc, Graphics* graphics);

private:
	ID3D11Buffer* _buffer;
};

