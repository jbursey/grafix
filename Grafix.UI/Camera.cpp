#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Init(float x, float y, float z, float lookX, float lookY, float lookZ, int width, int height, float nearZ, float farZ)
{
	_position = DirectX::XMFLOAT4(x, y, z, 1);
	_up = DirectX::XMFLOAT4(0, 1, 0, 0); //w = 0 = vector
	_lookAt = DirectX::XMFLOAT4(0, 0, 1, 0);	

	DirectX::XMMATRIX identityMatrix = DirectX::XMMatrixIdentity();
	DirectX::XMStoreFloat4x4(&_worldToCamera, identityMatrix);

	DirectX::XMMATRIX perspectiveMatrix = DirectX::XMMatrixPerspectiveLH(width, height, nearZ, farZ);
	DirectX::XMStoreFloat4x4(&_cameraToProjection, perspectiveMatrix);
}

DirectX::XMFLOAT4X4 Camera::GetCameraMatrix()
{
	return _worldToCamera;
}

DirectX::XMFLOAT4X4 Camera::GetProjectionMatrix()
{
	return _cameraToProjection;
}
