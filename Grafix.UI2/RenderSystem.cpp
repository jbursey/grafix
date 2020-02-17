#include "RenderSystem.h"



RenderSystem::RenderSystem()
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::Render()
{
	
	float rgba[4];
	rgba[0] = 0;
	rgba[1] = 0;
	rgba[2] = 0;
	rgba[3] = 1;
	_context->ClearRenderTargetView(_rtv, rgba);

	_dxgiSwapChain->Present(0, 0);
}
