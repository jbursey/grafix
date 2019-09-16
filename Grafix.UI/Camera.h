#pragma once
#include <DirectXMath.h>
class Camera
{
public:
	Camera();
	~Camera();
	void Init(float x, float y, float z, float lookX, float lookY, float lookZ, int width, int height, float nearZ, float farZ);
	DirectX::XMFLOAT4X4 GetCameraMatrix();
	DirectX::XMFLOAT4X4 GetProjectionMatrix();

private:
	DirectX::XMFLOAT4X4 _worldToCamera;
	DirectX::XMFLOAT4X4 _cameraToProjection;

	DirectX::XMFLOAT4 _position;
	DirectX::XMFLOAT4 _up;
	DirectX::XMFLOAT4 _lookAt;
};

