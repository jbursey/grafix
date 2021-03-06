#pragma once
#include <DirectXMath.h>
#include "GrafixConstants.h"
class Camera
{
public:
	Camera();
	~Camera();
	void Init(int width, int height, float nearZ, float farZ);
	void SetPosition(float x, float y, float z);
	void SetOrientation(float roll, float pitch, float yaw);
	void Resize(int width, int height, float nearZ, float farZ);
	DirectX::XMMATRIX GetCameraMatrix();
	DirectX::XMMATRIX GetProjectionMatrix();
	void MoveForward();
	void MoveBackward();
	void TurnRight();
	void TurnLeft();
	void MoveUp();
	void MoveDown();

	DirectX::XMFLOAT3 GetPosition();

private:
	float _x;
	float _y;
	float _z;

	float _roll;
	float _pitch;
	float _yaw;

	DirectX::XMMATRIX _projectionMatrix;

	//DirectX::XMFLOAT4 _position;
	DirectX::XMFLOAT4 _up;
	DirectX::XMFLOAT4 _lookAt;
};

