#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Init(int width, int height, float nearZ, float farZ)
{
	//_position = DirectX::XMFLOAT4(0, 0, 0, 1);
	_up = DirectX::XMFLOAT4(0, 1, 0, 0); //w = 0 = vector
	_lookAt = DirectX::XMFLOAT4(0, 0, 1, 0);	

	_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(75.0 * (DirectX::XM_PI / 180.0), width / height, nearZ, farZ);
}

void Camera::SetPosition(float x, float y, float z)
{
	_x = x;
	_y = y;
	_z = z;
}

void Camera::SetOrientation(float roll, float pitch, float yaw)
{
	_roll = roll;
	_pitch = pitch;
	_yaw = yaw;
}

DirectX::XMMATRIX Camera::GetCameraMatrix()
{
	//-- mat = S*R*T
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(1.0, 1.0, 1.0);
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(_x, _y, _z);
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(_roll, _pitch, _yaw);
	
	return S * R * T;
}

DirectX::XMMATRIX Camera::GetProjectionMatrix()
{
	return _projectionMatrix;
}

void Camera::MoveForward()
{
}

void Camera::MoveBackward()
{
}
