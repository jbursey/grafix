#pragma once
#include <DirectXMath.h>

struct CBPerEntity
{
	DirectX::XMFLOAT4X4 ModelToWorld;
	DirectX::XMFLOAT4X4 WorldToCamera;
	DirectX::XMFLOAT4X4 CameraToScreen;
};


struct CBPerFrame
{

};

