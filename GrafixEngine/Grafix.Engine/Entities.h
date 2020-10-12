#pragma once
#include <vector>
#include "RenderingComponent.h"
#include "PositionComponent.h"
#include "LightComponent.h"

struct Entities
{
public:
	std::vector<RenderingComponent*> RenderingComponents;
	std::vector<PositionComponent*> PositionComponents;
	std::vector<LightComponent*> LightComponents;
};
